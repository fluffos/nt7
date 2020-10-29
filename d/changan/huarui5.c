//Room: huarui5.c

inherit ROOM;

void create ()
{
        set ("short", "华瑞街");
        set("long", @LONG
华瑞街是长安城南一条东西向的大道，也是长安城的居民区。一
条碎石子铺成的街坊，南边可见一些民居住宅，街头有炊烟袅袅飘来
青柴的香味。不远处传来家家户户舂米的声音，还有大户人家榨香油
的醇香味。路边三五个小孩正在拍手唱歌玩耍着。　　
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/minju5",
                "west" : "/d/changan/huarui4",
                "east" : "/d/changan/huarui6",
                "north" : "/d/changan/zahuopu",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}