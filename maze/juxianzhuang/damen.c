// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "游府大门");
        set("long",  @LONG
游氏双雄身为一方豪富，却不失武林中人的本色，宅邸之中的演
武场修葺得尤为广阔，场中旌旗蔽空，樯帆林立，场边的兵器架上摆
放着刀、枪、剑、戟、锤等十八般兵器，被家丁们擦拭得寒光闪闪。
游氏双雄嗜武成痴，时常邀请武林中的前辈耆宿、后起之秀来庄中比
试切磋。
LONG);
        set("outdoors", "luoyang");
        set("region", "luoyang");
        set("no_fight", 1);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"  :  "/d/luoyang/suishi2",
                "west"  :  __DIR__"dayuan",
        ]));
        set("objects",([
                __DIR__"npc/xu" : 1,
        ]));

        setup();
        //replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        object ob, room;

        if( me->query_temp("juxianzhuang_step") != 6 &&
            me->query_temp("juxianzhuang_step") != 13 )
                if( objectp(present("xu zhanglao", environment(me))) && dir == "west" )
                        return notify_fail("徐长老拦住你说：你来洛阳聚贤庄撒野？快走开！\n");

        if( me->query_temp("juxianzhuang_step") == 13 && dir == "west" )
        {
                int valid;

                valid = FUBEN_D->valid_enter(me, "juxianzhuang");
                if( valid >=1 )
                {
                        room = get_object("/f/juxianzhuang/"+me->query("id")+"/zhengting");
                        ob = new("/maze/juxianzhuang/npc/azhu");
                        ob->move(room);
                        ob = new("/maze/juxianzhuang/npc/qiaofeng2");
                        ob->move(room);
                        FUBEN_D->enter_fuben(me, "juxianzhuang");
                        return -1;
                }
                else
                        return notify_fail("你无法进入聚贤庄副本。\n");
        }

        return ::valid_leave(me, dir);
}
