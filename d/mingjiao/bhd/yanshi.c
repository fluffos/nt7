// yanshi.c 岩石
// snowman 16.12.98
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
string sea();
void create()
{
	set("short", HIW"岩石"NOR);
        set("long", @LONG
这是一块露出水面的岩石。但见那火柱的周围一片青绿，原来这
里是一个极大的岛屿。岛屿西部都是尖石嶙峋的山峰，奇开怪样，莫
可名状，岛东却是一片望不到尽头的平野，乃火山灰倾入大海而成。
此处虽处北极，但火山万年不灭，岛上气侯便和长白山、黑龙江一带
相似。岛的西部有一山顶有一山顶正在帽出黑烟。往北便是一片片大
绿野。岩石的南部是海边(sea），有几块浮基正向南漂流。
LONG );
        set("item_desc", ([
		"sea" : (: sea :),
        ]) );
	set("exits",([
		"north" : __DIR__"pingyan1",
	]));
	set("outdoors", "冰火岛");
	setup();
}

void init()
{
     if(!this_player()->query_condition("cold_wind") && !wizardp(this_player()))
        this_player()->apply_condition("cold_wind", 1);
	add_action("do_make","make");
        add_action("do_push","tui");
        add_action("do_enter","enter");
}

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
                          message_vision("$N象猴子一样蹦得老高，两下就窜上了帆船。\n\n", me);
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

        if(!query("boat")) return notify_fail("推什么？\n");
        if( arg=="chuan" || arg=="船" ) {
            if(me->is_busy()) return notify_fail("你正忙着呢。\n");
            if(query("boat_on_sea")) return notify_fail("岸边有艘帆船呢，你再推下去一艘，它们会相撞的。\n");
            me->start_busy(5);
            add("boat", -1);
            message_vision("$N使出吃奶的劲，将用树干制成的帆船推进了大海。\n\n", me);
            EMOTE_D->do_emote(me,"touch", me->query("id"));
            me->add("jingli", -50);
            ob=new("/clone/misc/boat");
            ob->set("boat_of", base_name(this_object()));
            ob->set_temp("stepe", 200);
            ob->set_temp("stepn", 945);
            ob->move("/clone/misc/sea");
            set("boat_on_sea", 1);
            return 1;
        }
}       

int do_make(string arg)
{
        object me, ob, weapon;
        int i;
        string msg;
        me = this_player();
        weapon = me->query_temp("weapon");
        i = query("make_times");

        if( arg=="chuan" || arg=="船" ) {
            if(me->is_busy()) return notify_fail("你正忙着呢。\n");
            me->start_busy(5);
            if(!objectp(ob = present("shu gan", environment(me)))
               && !objectp(ob = present("shu gan", me)))
                     return notify_fail("你要用什么材料造船？\n");
            switch(i){
                case 0: if(!weapon || weapon->query("flag")!=4) return notify_fail("你需要一件锋利的工具，才能剖开树干。\n");
                        msg = "$N将树干剖开，并排，再用藤条将它们牢牢地困紧。\n"; 
                        add("make_times", 1); break;
                case 1: msg = "$N将树干上的树皮拨下来，打紧，再用腾条穿孔做成了帆。\n"; 
                        add("make_times", 1); break;
                case 2: msg = "$N将树干掏空，打磨了一翻，然后用掏出的木头做成了浆，舵等用具。\n"; 
                        add("make_times", 1); break;
                case 3: msg = "$N将一根树干削圆削细，仔细量了尺寸，做成了主桅杆。\n"; 
                        add("make_times", 1); break;
                case 4: msg = "$N将帆支起，又加固了主桅，一条船总算是做好了。\n";
                        delete("make_times");
                        add("boat", 1);
                        break;
                default: break;
            }
            me->add("jingli", -100);
            destruct(ob);
            message_vision(msg, me);
            return 1;
        }
        else return notify_fail("你要做什么？\n");
}       

string sea()
{   
       string msg;
       int boat;
       boat=query("boat_on_sea");
    
       msg = "\n那是一片汪洋，一望无际，海中有无数的浮冰。\n";
       if(boat)
          msg += "岸边停放着一只简陋的帆船，正随波左右摇动。从这里就可以上去(enter)。\n";        
          msg += "这里宽阔平坦，看来可以是个很好的工场。\n";
       if(query("make_times") >= 1){ 
            if(query("make_times") >= 4) msg += "有一只用巨树树干制成的简陋帆船的船体，看来是快要完成了。\n";
            else msg += "一旁放有几根巨树的树干，已经被剖开成了两半。\n";  
       }
       if(query("boat")) msg += "岸边放有用巨树树干制成的简陋帆船，如果使劲推，可以把它推(tui)下水去。\n";
       return msg;       
}
