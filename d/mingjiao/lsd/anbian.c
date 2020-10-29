// anbian.c 岸边
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;

void home( object ob );
void create()
{
        set("short", GRN"岸边"NOR);
        set("long", @LONG
只见岸边数里之外树木葱翠，奇峰挺拔，耸立着好几座高山。岛
东端山石直降人入海，并无浅滩，帆船吃水较深，却可以泊在岸边。
这时你看见不远的有一块颇为平整的岩石，上面被人用利器刻着『灵
蛇岛』三个大字，其侧还有几个看不太清的小字(zi)。往东而上是一
个很高的山岗，再上面是一座山峰。海滩上有几只海船，看来可以推
(tui)下海去。
LONG );
        set("exits", ([ 
                "eastup" : __DIR__"shanguang",
        ]));
        set("item_desc", ([
                "zi" :HIR"\t\t踏足灵蛇岛，必死！\n"NOR
        ]));
        set("boat", 1);
        set("outdoors", "灵蛇岛");
        setup();
}

void init()
{
        // add_action("do_push","tui");
        add_action("do_enter","enter");
}

/*
int do_enter()
{
        object me, sea, *inv;
        int i;
        me = this_player();        
        if(!query("boat_on_sea")) return 0;
        if(!(sea = find_object("/clone/misc/sea")))
             sea = load_object("/clone/misc/sea");
        if(sea = find_object("/clone/misc/sea")){
             inv = all_inventory(sea);
             for(i= 0;i< sizeof(inv);i++){
                   if(inv[i]->query("boat_of") == base_name(this_object())){
                          message_vision("$N象猴子一样蹦得老高，两下就窜上了海船。\n\n", me);
                          me->move(inv[i]);
                          message("vision",me->name()+"象猴子一样蹦了上来。\n",environment(me), ({me}) );
                          return 1;
                   }
             }
        }
        else write("sea boat error, please call wizard. \n");
        return 1;
}       

int do_push(string arg)
{
        object me, ob;
        me = this_player();
        
        if( arg=="chuan" || arg=="船" ) {
            if(me->is_busy()) return notify_fail("你正忙着呢。\n");
            if(!query("boat")) return notify_fail("岸上已经没有海船了。\n");
            if(query("boat_on_sea")) return notify_fail("岸边有艘海船呢，你再推下去一艘，它们会相撞的。\n");
            me->start_busy(5);
            add("boat", -1);
            message_vision("$N使出吃奶的劲，将海船推进了大海，现在总算可以上船(enter)了。\n", me);
            EMOTE_D->do_emote(me,"touch", me->query("id"));
            me->add("jingli", -50);
            ob=new("/clone/misc/boat2");
            ob->set("boat_of", "/d/mingjiao/lsd/anbian");
            ob->set_temp("stepe", 98);
            ob->set_temp("steps", 5);
            ob->move("/clone/misc/sea");
            set("boat_on_sea", 1);
            return 1;
        }
}       

void reset()
{
        set("boat", 1);
        ::reset();
}
*/
int do_enter ( string arg )
{
        object ob ;
        string dir;
        if (! arg || arg != "chuan")
        {
                tell_object(this_player() , "你要 enter 哪儿？\n" ) ;
                return 1 ;
        }
        ob = this_player () ;
        message_vision("船夫一见有人上船，忙叫了一声：开船喽！\n", ob);
        message_vision("船夫升起帆，船就向西方航行。\n", ob);
        ob->move("/d/mingjiao/lsd/dahai") ;
        tell_object(ob, BLU "你在海上航行了三天三夜.......\n" NOR ) ;
        call_out("home", 10 , ob );
        return 1 ;
}
void home( object ob )
{
        tell_object(ob , "大船终于抵达了南海岸边。你走下船来。\n" ) ;
        ob->move("/d/beijing/haigang") ;
}


