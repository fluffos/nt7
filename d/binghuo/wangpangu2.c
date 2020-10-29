// Room: /binghuo/wangpangu2.c
// Date: Oct.28 1999 by Lonely

inherit ROOM;

void create()
{
/*
        set("short", "山谷");
        set("long", @LONG
四周长满了几百株合抱大松树。左首山峰前一堵大石壁，壁上刻
着廿四字(zi)，纵横开阖，宛如施展拳脚一般。但见笔划多的不觉其
繁，笔划少的不见其陋，其缩也凝重，似尺蠖之屈，其纵也险劲，如
狡兔之脱，淋漓酣畅，雄浑刚健，俊逸处如风飘，如雪舞，厚重处如
虎蹲，如象步。其中两个“不”字，两个“天”字，但两字写来形同
而意不同，气似而神不似，变化之妙，又是另具一功。尤其是“锋”
字最后一笔，直划下来，当真是星剑光芒，如矢应机，霆不暇发，电
不及飞。
LONG );
*/
        set("short", "扬刀立威会场");
        set("long", @LONG
这里是扬刀立威会场，一片青草地上摆着七八张方桌，除了东首第一席外，
每张桌旁都已坐了人，有海沙派、巨鲸帮、神拳门等等各派弟子。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "wangpan");
        set("item_desc", ([
                "zi": 
"　　　　※※※※※※※※※※※※※※※※※※※※※※※\n"
"　　　　※※※※　　        　　　　　　　　　※※※※\n"
"　　　　※※※※　　谁　倚　莫　号　宝　武　　※※※※\n"
"　　　　※※※※　　        　　　　　　　　　※※※※\n"
"　　　　※※※※　　与　天　敢　令　刀　林    ※※※※\n"
"　　　　※※※※　　        　　　　　　　　　※※※※\n"
"　　　　※※※※　　争　不　不　天　屠　至　　※※※※\n"
"　　　　※※※※　　        　　　　　　　　　※※※※\n"
"　　　　※※※※　　锋　出　从　下　龙　尊　　※※※※\n"
"　　　　※※※※　　　　　　                　※※※※\n"
"　　　　※※※※※※※※※※※※※※※※※※※※※※※\n",
        ]));
        set("exits", ([
                "north"     : __DIR__"wangpangu1",
                "northeast" : __DIR__"wangpanlin",
        ]));
        set("objects", ([
                "/d/tulong/tulong/npc/mai" : 1,
                "/d/tulong/tulong/npc/guo" : 1,
                "/d/tulong/tulong/npc/yin" : 1,
                "/d/tulong/tulong/npc/yuan" : 1,
                "/d/tulong/tulong/obj/ding" : 1,
                "/d/tulong/tulong/npc/zhang" : 1,
                "/d/tulong/tulong/npc/chang" : 1,
        ]));
        setup();
}

void reset()
{

        object item, con;
        ::reset();
        con = present( "ding", this_object());
        item = find_object("/d/tulong/obj/tulongdao");
        if( !objectp(item) || !environment(item) ) {
                item = get_object("/d/tulong/obj/tulongdao");
                item->move(con);
                item->start_borrowing();
        }
}

