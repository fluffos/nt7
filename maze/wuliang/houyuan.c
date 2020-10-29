// Room: houyuan.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "后院");
	set("long", @LONG
后院乃剑湖宫清闲之所，一排茶花相间而开，青藤绕树，两三果子忽隐忽
现。靠墙放着一张长桌子，上面放了些水果，还有一只大水壶。几只青瓷小碗
洗得干干净净。北面是一片松林，也是无量剑派的禁地。
LONG
	);
	set("exits", ([ 
	    "south" : __DIR__"jhg",
            "north" : __DIR__"songlin1",	    
        ]));
        set("outdoors", "大理");
	setup();
}