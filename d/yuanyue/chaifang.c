// This program is a part of NITAN MudLIB

inherit ROOM;
void create()
{
        set("short", "柴房"); 
        set("long", @LONG
圆月山庄的柴房好像并不是堆柴的，而是关人的。柴房里有蜘蛛，
有老鼠，有狗屎猫尿，烂锅破碗，有用剩下的煤屑(breeze)。几乎什
麽都有，就是没有柴连根柴都没有。
LONG );
        set("type","house");
        set("indoors", "wansong");
        set("exits",([
                "south":__DIR__"grass4",
        ]) );

        set("item_desc", ([
                "煤屑": "柴房里到处都是煤屑，你似乎可以打扫一下（ｄｉｇｈｔ）。\n",
                "breeze": "柴房里到处都是煤屑，你似乎可以打扫一下（ｄｉｇｈｔ）。\n",
        ]) ); 
        set("coor/x",-590);
        set("coor/y",260);
        set("coor/z",80);
        setup();
        
} 
void init()
{
        add_action ("do_dight", "dight");
} 
int do_dight()
{               
        object mh,bo;
        int eff_qi;
        /*
        if (!present("sao ba",this_player())) 
                return notify_fail("你身上没有扫把，怎么打扫？\n");
        */
        eff_qi=query("qi", this_player());
        if( eff_qi<query("max_qi", this_player())/10 )
        {
                return notify_fail("你太累了，怎么打扫？\n");
        }
        this_player()->receive_damage("qi",query("max_qi", this_player())/10);
        if( query("dighted", this_object()) )
        {       message_vision("$N拿着扫把二话不说打扫起来，\n顿时柴房里扬起漫天的灰尘，简直呛得透不过气，\n辛苦了一番，屋子总算干净了些。\n\n", this_player() );
                return 1;
        }
        else if (random(5)) 
        {
                message_vision("$N拿着扫把二话不说打扫起来，\n顿时柴房里扬起漫天的灰尘，简直呛得透不过气，\n辛苦了一番，屋子总算干净了些。\n\n", this_player());
                return 1;
        }
        else 
        {
                message_vision("$N拿着扫把辛辛苦苦地扫着，突然在一个黑暗的角落里，似乎发现有一个小木盒子。\n", this_player());
                set("dighted", 1, this_object());
                mh=new(__DIR__"obj/muhe");
                bo=new("/clone/book/mojiao");
                bo->move(mh);
                mh->move(this_player());
                return 1;
        }
        return 0;
} 
void reset(){
        ::reset();
      
        if( query("dighted", this_object())){
                delete("dighted", this_object());
        }
        return;
}        
