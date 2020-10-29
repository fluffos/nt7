// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "密道");
	set("long", @LONG
这里是密道，前面隐约能看见亮光，听见一些声音，看样子到洞口了。你
走到洞口前，立刻看见了熟悉的道路。
LONG
	); 

	set("exits", ([
	      "out" : "/d/dali/shanlu3",
              "northup" : __DIR__"midao4",
	]));

	setup(); 
}

int valid_leave(object me, string dir)
{
      if ( dir == "out"){
       write("\n你出得地道，强光闪耀，一时之间竟然睁不开眼。\n\n");
       }
       return 1;
//     return ::valid_leave(me, dir);
}