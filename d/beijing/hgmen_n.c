inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","皇宫北门");
        set("long", @LONG
这里便是皇宫的北门，丈高的朱红大门敞开着，门上金色的铆钉
闪闪发光。大门两旁站着两排神情严肃的卫兵，不停的打量着过往的
行人。灿烂的阳光直射在巍峨雄伟的古城墙上，使得城墙上方『紫禁
城』三个烁金大字显得格外的耀眼。东厂和西厂两个京城的特务机构
架设在皇宫北门的左右两侧。从北方穿过地安门可以到达北京的北城
郊。[2；37；0m
LONG );
        set("exits", ([
                "south" : "/d/huanggong/jingshan",
                "north" : "/d/beijing/dianmen",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing2" : 1,
                "/d/beijing/npc/bing3" : 1,
                "/d/beijing/npc/yuqian1" : 1,
        ]));
        set("no_fight", 0);
	set("coor/x", -2800);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (objectp(ob = present("guan bing", environment(me))) && dir == "south")
                return notify_fail(ob->name() + "伸手拦住你朗声说道：皇宫重地，岂容寻常百姓出入。\n\n");
        if (objectp(ob = present("shi wei", environment(me))) && dir == "south")
                return notify_fail(ob->name() + "伸手拦住你朗声说道：皇宫重地，岂容寻常百姓出入。\n\n");
        return ::valid_leave(me, dir);
}