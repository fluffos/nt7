// /u/cool/tls/wanfodong.c
// cool 1998.2.13

inherit ROOM;

void create()
{
	set("short", "万佛洞");
	set("long", @LONG
你走出忘雪亭来到山壁边，眼前一座古洞，洞口上面书有三个大
字“万佛洞”，这洞隐藏在寺后深处，寻常人等恐怕找也找不到这里。
LONG);
	set("exits", ([
	      "up" : __DIR__"wxt",
              "enter" : __DIR__"wfd2",	
        ]));
	set("coor/x",-390);
  set("coor/y",-250);
   set("coor/z",30);
   setup();
}

