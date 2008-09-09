/***************************************************************************
*   Copyright (C) 2007 by BOP                                             *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#include <QtCore>

#include <eb/eb.h>
#include <eb/binary.h>
#include <eb/text.h>
#include <eb/font.h>
#include <eb/appendix.h>
#include <eb/error.h>

#include "ebook.h"
#include "ebhook.h"
#include "textcodec.h"

const int HitsBufferSize = 10000;
const int TextBufferSize = 4000;
const int TextSizeLimit = 2800000;

QList <CandItems> EbMenu::topMenu()
{

    EB_Position pos;

    if (!menu(&pos)) {
        QList<CandItems> i;
        return i;
    }

    QString t;
    return candidate(pos, &t);

}

EBook::EBook(HookMode hmode)
    : EbCore(hmode)
{
}

EBook::~EBook()
{
}

int EBook::hitMultiWord(int maxcnt, const QStringList &words, SearchType stype)
{
    hits.clear();
    if ((stype == SearchKeyWord && !isHaveWordSearch()) ||
        (stype == SearchCrossWord && !isHaveCrossSearch()) )
        return 0;

    int word_num = words.count();

    char** word_list = new char*[word_num + 1];
    QList <QByteArray> bword_list;
    for (int i = 0; i < word_num; i++ ) {
	bword_list << utfToEuc(words[i]);
	word_list[i] = bword_list[i].data();
    }
    word_list[word_num] = NULL;

    if ( maxcnt <= 0 )
        maxcnt = HitsBufferSize;
    int hit_count;
    int count = 0;
    for (;;) {
        EB_Error_Code ecode;
        if (stype == SearchKeyWord) {
            ecode = eb_search_keyword(&book, word_list);
        } else {
            ecode = eb_search_cross(&book, word_list);
        }
        if (ecode != EB_SUCCESS) {
            ebError("eb_search_cross", ecode);
            break;
        }

        EB_Hit wrk[HitsBufferSize];
        ecode = eb_hit_list(&book, HitsBufferSize, wrk, &hit_count);
        if (ecode != EB_SUCCESS) {
            ebError("eb_hit_list", ecode);
            break;
        }

        for (int i = 0; i < hit_count; i++) {
            bool same_text = false;
            foreach(EB_Hit h, hits) {
                if (wrk[i].text.page == h.text.page &&
                    wrk[i].text.offset == h.text.offset) {
                    same_text = true;
                    break;
                }
            }
            if (same_text) continue;

            hits << wrk[i];
            count++;
            if (count >= maxcnt) break;
        }

        break;
    }
    delete word_list;

    return count;
}

int EBook::hitWord(int maxcnt, const QString &word, SearchType type)
{
    hits.clear();
    if ( maxcnt <= 0 ) maxcnt = HitsBufferSize;
    EB_Error_Code ecode;
    QByteArray bword = utfToEuc(word);
    if (type == SearchWord) {
	if (!isHaveWordSearch())
	    return 0;
        ecode = eb_search_word(&book, bword);
        if (ecode != EB_SUCCESS) {
            ebError("eb_search_word", ecode);
            return -1;
        }
    } else if (type == SearchEndWord) {
	if (!isHaveEndwordSearch())
	    return 0;
        ecode = eb_search_endword(&book, bword);
        if (ecode != EB_SUCCESS) {
            ebError("eb_search_endword", ecode);
            return -1;
        }
    } else {
	if (!isHaveWordSearch())
	    return 0;
        ecode = eb_search_exactword(&book, bword);
        if (ecode != EB_SUCCESS) {
            ebError("eb_search_exactword", ecode);
            return -1;
        }
    }

    EB_Hit wrk[HitsBufferSize];
    int hit_count;
    ecode = eb_hit_list(&book, HitsBufferSize, wrk, &hit_count);
    if (ecode != EB_SUCCESS) {
        ebError("eb_hit_list", ecode);
        return -1;
    }

    int count = 0;
    for (int i = 0; i < hit_count; i++) {
        bool same_text = false;
        foreach (EB_Hit h, hits) {
            if (wrk[i].text.page == h.text.page &&
                wrk[i].text.offset == h.text.offset) {
                same_text = true;
                break;
            }
        }
        if (same_text)  continue;
        hits << wrk[i];

        count++;
        if (count >= maxcnt) break;
    }
    return count;
}

int EbAll::hitFull(int maxcnt)
{
    hits.clear();
    EB_Error_Code ecode;
    EB_Position position;
    int count = 0;

    if (firstSeek) {
        ecode = eb_text(&book, &position);
        if (ecode != EB_SUCCESS) {
            ebError("eb_text", ecode);
            return -1;
        }
        firstSeek = false;
    } else {
        position = seekPosition;
    }
    EB_Hit hit;
    hit.heading = position;
    hit.text = position;
    hits << hit; 
    count++;
    while (count <= maxcnt) {
        ecode = eb_seek_text(&book, &position);
        if (ecode != EB_SUCCESS) {
            ebError("eb_seek_text", ecode);
            break;
        }
        ecode = eb_forward_text(&book, &appendix);
        if (ecode != EB_SUCCESS) {
            if (ecode == EB_ERR_END_OF_CONTENT &&
                position.page < book.subbook_current->text.end_page) {
                //qDebug() << "hitFull : page=" << position.page
                //         << "offset=" << position.offset
                //         << "end page=" << book.subbook_current->text.end_page;
                ecode = eb_tell_text(&book, &position);
                //qDebug() << "tell_text : page=" << position.page
                //         << "offset=" << position.offset;
                if (ecode != EB_SUCCESS) {
                    ebError("eb_tell_text", ecode);
                    break;
                }
                if (position.page >= book.subbook_current->text.end_page) {
                    //    qDebug() << "hitFull : page=" << position.page
                    //             << "offset=" << position.offset ;
                    break;
                }
                position.offset += 2;
            } else {
                break;
            }
        } else {
            ecode = eb_tell_text(&book, &position);
            if (ecode != EB_SUCCESS) {
                ebError("eb_tell_text", ecode);
                break;
            }
        }
        if (count < maxcnt) {
            EB_Hit hit;
            hit.heading = position;
            hit.text = position;
            hits << hit; 
        }
        count++;
    }
    seekPosition = position;
    return count - 1;
}

int EbAll::setStartHit(const EB_Position &text_pos)
{
    seekPosition = text_pos;
    firstSeek = false;
    return 0;
}

