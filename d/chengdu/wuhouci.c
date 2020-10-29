// Room: wuhouci.c
// Date: Feb.14 1998 by Java

inherit ROOM;
string look_gaoshi();
void create()
{
        set("short", "诸葛亮殿");
        set("long", @LONG
这里是武侯祠的正殿诸葛亮殿。武侯羽扇纶巾一如生前。两边诸
葛瞻和诸葛尚父子塑像也栩栩如生。挂在殿门两壁的，由诗圣杜甫笔
下流露的千古名联：『三顾频繁天下事，两朝开济老臣心。』道尽了
这个千古风范的一生心事。
LONG );
        set("exits", ([
            "southdown" : __DIR__"liubeidian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15240);
	set("coor/y", -1840);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}