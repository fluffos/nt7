// ken 1999.12.9

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "幽香湖");
	set("long", @LONG
这是一个碧清的小湖，湖边盛开着各式各样的奇花异草。
一阵幽风袭面而来，顿觉四周清香暗涌。北面是陡峭的山崖，
刚才所见的灯光似乎就来自这座山上。
LONG
	);
	set("exits", ([ 
  "west" : __DIR__"caodi",
]));
	set("coor/x",-20);
	set("coor/y",1050);
	set("coor/z",0);
	setup();
}
void init()
{
        add_action("do_fillwater", "fillwater");
}
int do_fillwater(string arg)
{
        object *list, ob;
        int i, can_fillwater;
        string dir;

        if( !arg || arg=="" ) return 0;

        if( arg=="skin" || arg=="wineskin" ) {
                list = all_inventory(this_player());
                i = sizeof(list);
                can_fillwater = 0;
                while (i--) {
                  if (((string)list[i]->query("liquid/type") == "alcohol")
 || ((string)list[i]->query("liquid/type") == "water")         ) {
                        ob = list[i];
                        can_fillwater = 1;
                        ob->set("liquid", ([
                                "type": "water",
                                "name": "幽香湖水",
                                "remaining": 15,
                                "drunk_apply": 6,
                        ]) );
                        write("你从幽香湖里装满了水！ \n");
                        return 1;
                   }
                }
                if (can_fillwater ==0) {
                        write("你没有装水的东西啊....\n");
                        return 1;
                }
        }
        else {
                write("你要往什么东西里灌水？\n");
        }
        return 1;
}
