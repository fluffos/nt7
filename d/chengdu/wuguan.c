// Room: wuguan.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "金牛武馆");
        set("long", @LONG
「金牛武馆」在江湖中很有名声，很多大侠自小就是从这里走进
江湖。虽然他们在江湖早已成名立万，这里的师傅年纪也都大了，却
是他们的启蒙业师，他们也常回来看望师傅们，因此这里长久得到黑
白两道的尊重，不容侵犯。这里是武馆大厅。馆主马五德在此请授：
基本轻功，基本内功，基本招架，基本手法，^M基本刀法。  墙上贴
着个贴子(tiezi)。
LONG );
        set("objects", ([
                __DIR__"npc/mawude" : 1,
                __DIR__"npc/zhangfang" : 1,
        ]));
         set("no_fight",0);
        set("no_steal",1);
        set("no_beg",1);
        set("item_desc", ([
            "tiezi" : @TEXT
金牛武馆敬启者：不须把所有的基本武功学全。必要的基本武功是：

㈠ 基本内功
㈡ 基本轻功
㈢ 基本招架
㈣ 基本拳脚：由基本爪法、基本手法、基本掌法、基本指法、基
             本爪法以及基本拳法任选一种。
㈤ 基本兵器：由基本刀法、基本棍法、基本剑法、基本杖法、基
             本棒法以及基本暗器任选一种。

----------------------------------------------------------
「金牛武馆」所传授基本武功
----------------------------------------------------------
１）基本轻功 (dodge)            ８）基本拳法 (cuff)
２）基本内功 (force)            ９）基本刀法 (blade)
３）基本招架 (parry)            １０）基本棒法 (stick)
４）基本爪法 (claw)             １１）基本棍法 (club)
５）基本手法 (hand)             １２）基本杖法 (staff)
６）基本掌法 (strike)           １３）基本剑法 (sword)
７）基本指法 (finger)           １４）基本暗器 (throwing)
----------------------------------------------------------
学习命令是: xue 师傅名 武功技能
TEXT
        ]) );
        set("exits", ([
                "southwest" : __DIR__"northroad3",
                "east"      : __DIR__"wuguanchen",
                "south"     : __DIR__"wuguanlong",
                "west"      : __DIR__"wuguanxiao",
                "north"     : __DIR__"wuguanliu",
                "up"        : __DIR__"practice",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15200);
	set("coor/y", -1800);
	set("coor/z", 0);
	setup();
}
int valid_leave(object me, string dir)
{
        if( present("ma wude", this_object()) && !query_temp("marks/jinniu_paied", me) && (dir == "up") )
        return notify_fail("马五德笑道: 那是本馆弟子才能进去的。\n");
        else  return 1;
}
