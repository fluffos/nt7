inherit ROOM;

protected string p = "";

void create()
{
        set("short", "泥泞小路");
        set("long", @LONG
这是一条的小岔路，地上总是像刚下过雨一样泥泞不堪，和
着一些腐烂的枯枝败叶，臭气熏天。正前方是块大石头，石头上
满是青苔和烂藤，挡住了西方的道路，不知道能否推开(push)石头，
但实在又不知道往哪个方向推。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "northeast" : __DIR__"lcd03",
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
                tell_object(me, "石头已经移开了。\n");
                return 1;
        }

        if(sizeof(p) > 10)
                p = "";

        switch (arg)
        {
                case "left":
                        p = "l";
                        tell_object(me, "你向左面使劲推了一下石头，沾了一手泥。\n");
                        return 1;
                case "right":
                        p += "r";
                        tell_object(me, "你向右面使劲推了一下石头，沾了一手泥。\n");
                        if( (sizeof(p) > 5) && (p[<6..] == "lrrrrr") )
                        {
                                p = "";
                                if(!query("exits/west"))
                                {
                                        set("exits/west", __DIR__"lcd05");
                                        call_out("remove_west", 5);
                                        tell_room(__FILE__, "石头向右面一动，露出了一个缝隙。\n");
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

protected void remove_west()
{
        if("exits/west")
        {
                delete("exits/west");
                p = "";
        }
}
