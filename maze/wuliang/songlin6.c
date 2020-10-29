// Room: songlin6.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "大松林");
	set("long", @LONG
你眼前骤然一黑，朦胧中，只见左右前后，到处都是铺天盖地的松树林。
几十丈高的大松树簇在一块，密实的枝叶象一蓬蓬巨伞般伸向天空，把阳光遮
得丝毫也无。尺把厚的松针积在地上，一脚踩下去，半天拔不出来。你似乎迷
失了方向，象没头苍蝇般到处乱闯。
LONG
	);
	set("exits", ([ 
		"south" : __DIR__"songlin"+(1+random(6)),
		"north" : __DIR__"songlin"+(1+random(6)),
		"east" : __DIR__"songlin"+(1+random(6)),
		"west" : __DIR__"songlin"+(1+random(6)),
        ]));
        set("outdoors", "大理");
	setup();
}

void reset()
{
	set("exits", ([ 
		"south" : __DIR__"songlin"+(1+random(6)),
		"north" : __DIR__"songlin"+(1+random(6)),
		"east" : __DIR__"songlin"+(1+random(6)),
		"west" : __DIR__"songlin"+(1+random(6)),
        ]));
}