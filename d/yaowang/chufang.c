inherit ROOM;

protected void refresh_table()
{
        object *inv,zhuozi;
        int i = 15;

        if(!objectp(zhuozi = present("wood table", this_object())))
                return;

        call_out("refresh_table",300);

        if( sizeof( (inv = all_inventory(zhuozi)) ) )
                foreach( object one in inv )
                        if(!one->is_food())
                        {
                                if(one->is_character())
                                        one->move(this_object());
                                else
                                        destruct(one);
                        }
                        else
                                i--;

        if(i > 0)
                while(i--)
                {
                        object food = new("/clone/food/jitui");
                        food->move(zhuozi);
                }
}

void create()
{
        set("short", "厨房");
        set("long", @LONG
这里就是厨房，这里最显眼的就是一口巨大的水缸。房子中
间的餐桌上放着各种吃食，几个厨子在走来走去的忙和着，渴了
就随便从水缸里舀(drink)点水喝。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"gd4",
]));

        set("objects", ([
                __DIR__"obj/table": 1,
]));

        setup();
        refresh_table();
}

void init()
{
        add_action("do_drink", "drink");
}

int do_drink(string arg)
{
          object me;
          me=this_player();

              if( query("water", me) >= me->max_water_capacity() )
     {
                     write("你已经喝太多了，再也灌不下一滴水了。\n"); 
                    return 1; 
             } 

        message_vision("$N在水缸边用杯子舀起水喝了几口。\n", me);
        addn("water", 20, me);
        if( (query("family/family_name", me) != "药王谷" )
        && (random(10) < 3) )
                me->apply_condition("scorpion_poison", 10);
        return 1;
}
