// Room: /binghuo/lingsheroom.c
// Date: Oct.28 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "山顶小屋");
        set("long", @LONG
这里是金花婆婆在岛上的居所。小屋是岛上漫山遍野生长的青竹
搭就。海风吹响，很是凉爽。四壁小竹窗，尽收窗外婆娑树影后的兰
天、白云、碧海和黄沙，主人把这收拾得极为清雅。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out" : __DIR__"lingshetop",
        ]));
        set("objects", ([
                CLASS_D("mingjiao")+"/daiqisi": 1,
        ]));
        setup();
}
void init()
{
        object weapon, ob, me = this_player();
        mapping weapon_prop;
        string *apply, type;

        if(objectp(ob = present("dai yisi", environment(me))) && living(ob))
        {
                weapon = new(WEAPON_DIR"treasure/jinhua");
                if ( weapon->violate_unique() )
                {
                        destruct( weapon );
                }
                else
                {
                        if(!present("duoming jinhua", ob))
                        {
                                weapon->move(ob);
                                weapon_prop=query("weapon_prop", weapon);
                                apply = keys(weapon_prop);
                                for(int i = 0; i<sizeof(apply); i++)
                                        addn_temp("apply/"+apply[i], weapon_prop[apply[i]], ob);
                                set_temp("weapon", weapon, ob);
                                ob->reset_action();
                                set("equipped", "wielded", weapon);
                        }
                }
        }
}
