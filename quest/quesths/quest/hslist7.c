#include <ansi.h>

mapping *quest = ({
        ([
                "id" :    "yue er",
                "name" :  "月儿",
                "bonus":  75,
                "type":   "杀",
        ]),
        ([
                "id" :    "cloth",
                "name" :  "布衣",
                "bonus":  50,
                "type":   "寻",
        ]),
        ([
                "id" :    "cloth",
                "name" :  "布衣",
                "bonus":  60,
                "type":   "征",
                "object": "/d/city/obj/cloth.c",
        ]),
        ([
                "id" :    "cloth",
                "name" :  "布衣",
                "bonus":  60,
                "type":   "送",
                "object": "/d/city/obj/cloth.c",
        ]),
});

mapping query_quest()
{
        return quest[random(sizeof(quest))];
}
