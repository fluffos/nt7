//Room: fangzhangshi.c

inherit ROOM;

void create ()
{
        set ("short", "方丈室");
        set("long", @LONG
方丈室很是朴素，房中除了一个木榻和一个书桌之外，再就别无
他物。书桌上放着几本关于佛经的书籍，还有一个破旧的木鱼。木榻
上叠有几方棉布薄换。西面通往大雄宝殿。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "west" : "/d/changan/baodian",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/huitong" : 1,
        ]));
        
        set("coor/x", -10720);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}