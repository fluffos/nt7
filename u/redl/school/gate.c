// This program is a part of NITAN MudLIB
// redl 2013/8
#include <ansi.h>
#include <room.h>
inherit ROOM;

int clean_up() { return 1;}

void create()
{
        set("short", "学堂大门");
        set("long",
"','''╭⌒╮⌒╮.',''',,',.'',,','',.   \n"
"    ╱◥██◣''o中国梦，树新风o.'',,',.   \n"
"   ｜田｜田田│ '',,',.o tree new bee o   \n"
" ------------------------------------\n"
);
                set("outdoors", "yangzhou");
                set("exits",([ /* sizeof() == 1 */
                        "north" : __DIR__"caochang",
                        "east": "/d/city/kedian4",
                 "southeast": "/d/city/swing",
                             "northeast" : "/u/redl/teleport/teleport",
                ]));
                set("objects", ([
                        __DIR__"npc/ying" : 1,
                        __DIR__"npc/chen" : 1,
        ]));

        set("no_dazuo",1);
        set("no_kill",1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);
                set("no_rideto", 1);
                set("no_flyto", 1);
                set("no_magic", 1);
        set("no_sleep_room", 1);

        setup();
}

void do_rndmove(object baby, string str)
{
        object room = environment(baby);
        if (!room || base_name(room)!=str) return;
        if (!query_temp("school/init", baby)) return;

        if (baby->is_busy()) {
                call_out("do_rndmove", 2, baby, str);
                return;
        }

        delete_temp("school/init", baby);
        baby->command("go north");
}

void do_emote(object ob, string str)
{
        object room = environment(ob);
        if (!room || base_name(room)!=str) return;

                switch (random(4)) {
                        case 0:
                        case 1:
                                ob->command("think 爸爸妈妈怎么还不来接我呢？");
                                break;
                        case 2:
                                ob->command("wuwu");
                                break;
                        case 3:
                                ob->command("lala");
                                break;
                }

}

void init()
{
        object ob = this_player();
        if (base_name(ob)=="/clone/user/baby") {
                ob->command("halt");
                call_out("do_emote", 2, ob, base_name(this_object()));

                set_temp("school/init", 1, ob);
                call_out("do_rndmove", random(4) + 4, ob, base_name(this_object()));
        }
}
