inherit ROOM;
string p = "";
void create()
{
        set("short", "羊肠小路");
        set("long", @LONG
这是一条蜿蜒曲折的小路，右面是一小片低矮的树林，左面
是陡峭的山壁。地上满是乱石子，有的还很尖利，看样子这里很
少有人来。正前方是一堆粗大的原木挡住了去路。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"ycl7",
]));

        set("outdoors", "yaowang");
        setup();
}
void init()
{
        add_action("do_push", "push");
}

int do_push(string arg)
{
        object me = this_player();

        if( query("exits/west") )
        {
                tell_object(me, "原木已经移开了。\n");
                return 1;
        }

        if(sizeof(p) > 10)
                p = "";

        switch (arg)
        {
                case "left":
                        p = "l";
                        tell_object(me, "你向左面使劲推了一下原木。\n");
                        return 1;
                case "right":
                        p += "r";
                        tell_object(me, "你向右面使劲推了一下原木。\n");
                        if( (sizeof(p)>5) && (p[<6..] == "lrrrrr") && (query_temp("murong_ask", me) || query("family/master_name",me) == "石万嗔") )
                        {
                                p = "";
                                if(!query("exits/north"))
                                {
                                        set("exits/north", __DIR__"ycl9");
                                        call_out("remove_north", 5);
                                        tell_room(__FILE__, "原木向左面一动，露出了一个缝隙。\n");
                                        return 1;
                                }
                                return 1;
                        }
                        return 1;
                default:
                        tell_object(me, "你要往哪个方向推？\n");
                        return 1;
        }
}

void remove_north()
{
        if("exits/north")
        {
                delete("exits/north");
                p = "";
        }
}
