// This program is a part of NITAN MudLIB 
// redl 2013/10
#include <ansi.h>
inherit ROOM;

#define STEP_RND 1000
#define COSTS2 ({4,3,2,1,0,-1,-2,-3,-4})
#define EXITS2 ({"north","south","west","east","northwest","northeast","southwest","southeast"})
#define SHORTZHEN ({HIB + "幻阵" + NOR, HIM + "迷阵" + NOR, HIG + "陷阵" + NOR, HIR + "杀阵" + NOR, HIY + "绝阵" + NOR, BRED + HIC + "劫阵" + NOR})

mapping default_dirs = ([
        "north":        "北方",
        "south":        "南方",
        "east":         "东方",
        "west":         "西方",
        "northup":      "北边",
        "southup":      "南边",
        "eastup":       "东边",
        "westup":       "西边",
        "northdown":    "北边",
        "southdown":    "南边",
        "eastdown":     "东边",
        "westdown":     "西边",
        "northeast":    "东北",
        "northwest":    "西北",
        "southeast":    "东南",
        "southwest":    "西南",
        "up":           "上面",
        "down":         "下面",
        "enter":        "里面",
        "out":          "外面",
]);

string load_name()
{
        return __DIR__"guangchang.c"->load_name();
}

int save_name(string arg)
{
        if (!arg || arg=="") 
                return notify_fail(NOR"没有arg来指定洞天名！\n"NOR);
        write_file(__DIR__"name.o", arg, 1);
        reload_object(this_object());
        return 1;
}

int clean_up() { return 1;}

string dtname = load_name();

int reload_me()//1分钟
{
        int lifetime = 0, level = 0, pro = 0;
        lifetime = __DIR__"data.c"->do_load("guarder_lifetime");
        level = __DIR__"data.c"->do_load("guarder_level");
        pro = __DIR__"data.c"->do_load("guarder_pro");
        set("guarder_lifetime", lifetime);
        set("guarder_level", level);
        set("guarder_pro", pro);
        dtname = load_name();
                if (lifetime >= 100 && level >= 300 && pro >= 50) 
                        set("zhen_type", 5);
                else if (lifetime >= 80 && level >= 200 && pro >= 40) 
                        set("zhen_type", 4);
                else if (lifetime >= 60 && level >= 150 && pro >= 30) 
                        set("zhen_type", 3);
                else if (lifetime >= 40 && level >= 100 && pro >= 20) 
                        set("zhen_type", 2);
                else if (lifetime >= 20 && level >= 50 && pro >= 10) 
                        set("zhen_type", 1);
                else 
                        set("zhen_type", 0);
        set("short", dtname + SHORTZHEN[query("zhen_type")]);
        return 1;
}

int create_exit2()
{
                object room;
                string outroom;

                outroom = __DIR__"data.c"->do_load2("outroom");
                if (!outroom || !objectp(room = get_object(outroom))) {
                //set("exits/out", "/u/redl/teleport/teleport");
        }
                else {
                        set("exits/out", outroom);
                        set("exits/dongtian", base_name(this_object()), room);
                        tell_room(this_object(), NOR HIB "只见空间扭曲，" + dtname + "洞天的大阵门户发生了变化。\n" NOR);
                        log_file("static/dongtian", "  -[" + dtname + "]-> " + outroom + "\n");
                }

        return 1;
}

int create_exit()
{
                string exitname;
                int cost;
                int *costs = COSTS2;
                string *exits = EXITS2;
                
                delete("exits");
                for(int i = random(2) + 7; i > 0; i--) {
                        exitname = exits[random(sizeof(exits))];
                        exits -= ({exitname});
                        cost = costs[random(sizeof(costs))];
                        costs -= ({cost});
                        set("exits/" + exitname, __FILE__);
                        set("costs/" + exitname, cost);
                }
                set("exits/enter", __DIR__"guangchang");
        create_exit2(); 
        
        return 1;
}

void create()
{
                reload_me();
        set("long",@LONG
这里是洞天前的护山大阵，阵法分为幻迷陷杀绝劫，各个高深莫测。
不知有多少贪图仙府遗珍的江湖儿女，就在此地落得个万劫不复。
LONG);

                set("no_sleep_room",1);
                //set("no_magic", 1);//准许招武器
                set("no_rideto", 1);
                set("no_flyto", 1);
                set("no_drift", 1);
                set("no_protect", 1);
                
                create_exit();
                set("flag_init", 1);
        set_heart_beat(97);
        setup();
}

void backup_exit()
{
        mapping exits = query("exits");
        string zhen, exn, *exitn = ({});
        if (undefinedp(exits) || !exits || !mapp(exits) || sizeof(exits)<7) {
                return;
        }
        foreach (string s in keys(exits)) {
                if (s!="enter" && s!="out") exitn += ({s});
        }
        //set("exitn", exitn);
        exn = exitn[random(sizeof(exitn))];
        set("exits_b/" + exn, query("exits/" + exn));
        delete("exits/" + exn);
        exn = default_dirs[exn];
        zhen = SHORTZHEN[query("zhen_type")];
        tell_room(this_object(), NOR + zhen + NOR + (random(2) ? "急速旋转" : "景象变幻") + (random(2) ? "中" : "之间") + exn + "的" + (random(2) ? "路" : "出口") + (random(2) ? "消失" : "不见") + "了。\n" + NOR);
}

void restore_exit()
{
        mapping exits = query("exits_b");
        string zhen, exn, *exitn = ({});
        if (undefinedp(exits) || !exits || !mapp(exits) || sizeof(exits)<1) {
                return;
        }
        foreach (string s in keys(exits)) {
                exitn += ({s});
        }
        //set("exitn", exitn);
        exn = exitn[random(sizeof(exitn))];
        set("exits/" + exn, query("exits_b/" + exn));
        delete("exits_b/" + exn);
        exn = default_dirs[exn];
        zhen = SHORTZHEN[query("zhen_type")];
        tell_room(this_object(), NOR + zhen + NOR + (random(2) ? "急速旋转" : "景象变幻") + (random(2) ? "中" : "之间") + exn + "的" + (random(2) ? "方向" : "通道") + (random(2) ? "出现" : "连通") + "了。\n" + NOR);
}

void heart_beat()
{
        object oroom, me = this_object();
        
        if ( stringp(query("exits/out", me)) && objectp(oroom = get_object(query("exits/out", me))) ) {
                set("exits/dongtian", base_name(me), oroom);
                tell_room(oroom, NOR HIG "只见空间扭曲，通往" + dtname + "洞天的阵门隐隐约约现出来(go dongtian)。\n" NOR);
        }
        
        if (!random(11 - query("zhen_type"))) {
                if (random(3)) restore_exit();
                        else backup_exit();
        }
        
        if (random(2)) set_heart_beat(97);
                else set_heart_beat(89);
}

int discmds() 
{ 
        tell_object(this_player(), "这里不允许你这样做。\n");  
        return 1;  
} 

int do_clear()
{
        __DIR__"data.c"->do_clear();
        return 1;
}

int do_sav(string arg)
{
        string key;
        int val;
        
        if (!arg || arg=="") 
                return notify_fail(NOR"没有指定arg:key val！\n"NOR);
        
        if (sscanf(arg, "%s %d", key, val)!=2) 
                return notify_fail(NOR"没有指定arg:key val！\n"NOR);
                
        return __DIR__"data.c"->do_save(key, val);
}

int have_ling(object me)
{
        object *inv;
        int i;
        object ob;// = present("dongtian ling", me);
        
        delete_temp("dongtian/dongtian_ling", me);

        inv = filter_array(all_inventory(me),
                           (: 
                           query("dt_value", $1)
                           :));
                           
        if (arrayp(inv) && sizeof(inv)) foreach (ob in inv) {
                //if (query("dt_name", ob) == dtname) break;
                if ((query("id", ob) == "dongtian ling") && (strsrch(base_name(ob), __DIR__) != -1)) break;
        }

        if ( !objectp(ob) )
        {
                return 0;
        }       
        
        i = query("dt_value", ob);
        
        if (!i)
                return 0;
       
        set_temp("dongtian/dongtian_ling", ob, me);
        return i;
}

int dest_ling(object me, int rnd)
{
        string msg;
        object ob = query_temp("dongtian/dongtian_ling", me);
        
        if (!ob || !objectp(ob))
                return 0;
                
        msg = NOR "\n$N轻轻一晃手里的$n..\n" NOR;
        message_vision(append_color(msg, CYN), me, ob);
        if (!rnd) {
                msg = NOR "$N手里的$n喀喇一声碎裂散掉了...\n\n" NOR;
                message_vision(append_color(msg, HIY), me, ob);
                destruct(ob);
                delete_temp("dongtian/dongtian_ling", me);
                return 0;
        }
        else {
                msg = NOR "浓雾里传来" + (random(2)? "一片" : "几声") + (random(2)? "尖叫" : "惨嚎") + 
                        "，诡秘的" + (random(2)? "傀儡" : "机关") + "人" + (random(2)? "兵器" : "盔甲") + (random(2)? "扔了一地" : "到处都是") + "。\n\n" NOR;
                message_vision(append_color(msg, CYN), me, ob);
                me->start_busy(1);
        }
        return 1;
}

void init() 
{ 
        object me = this_player();
        object ling = query_temp("dongtian/dongtian_ling", me);
        
        if ((playerp(me)) && 
                (!query("load_dt_time") || query("load_dt_time")+60 < time())) {//没有读取过，或者读取时间超过了一分钟
                        set("load_dt_time", time());
                        reload_me();
        }
        
        if ( wiz_level(me) > 5 ) {
                add_action("do_clear", "clear");
                add_action("save_name", "name");
                add_action("do_sav", "sav");
        }
        
        if( me->query_condition("killer") ) {
                        me->move(query("exits/out"));
                tell_object(me, NOR"你正在被通缉，不敢亵渎洞天！\n"NOR);
                return;
        }
        
        if( me->is_ghost() ) {
                        me->move(query("exits/out"));
                tell_object(me, NOR"等你还了阳再说吧。\n"NOR);
                return;
        }
        
        if (undefinedp(query_temp("dongtian/zhen/costs", me))) {
            if( me->in_team() ) me->command("team dismiss");
                set_temp("dongtian/zhen/costs", (STEP_RND / 2 + random(STEP_RND / 2)) * ((random(2))? 1 : -1), me);
                set_temp("dongtian/zhen/enter_times", time());
        } else {
                if ( (time() - query_temp("dongtian/zhen/enter_times")) > 1800 && !random(30) ) {
                        tell_object(me, NOR"你走得头昏眼花，晕沉沉地一头撞出了阵外。\n"NOR);
                        me->command("go out");
                }
        }
        
        if ((playerp(me) && wiz_level(me) < 6) || (base_name(me)=="/clone/user/baby")) add_action("discmds", ({  
                                                                "steal", "cast", "conjure", "array", "fight", 
                                                                "quit", "home", "exit", "recall", "ansuan", "touxi", 
                                                                "surrender", "chatroom", "rideto", "stab", 
                                                                "team", "kill", "hit", "guard", "ride", "array", "battle", "accept",
                }));  //不准主动下kill，防止使用大米引怪来协助获取经验
                
                if (__DIR__"guangchang.c"->owner_level(me)) {//已经是洞天的主人或者结义之一了的话,set 0
                        set_temp("dongtian/zhen/costs", 0, me);
                }

        if ( ling && objectp(ling) && query_temp("dongtian/zhen/last", me) > query_temp("dongtian/zhen/nextc", me) ) {//有令牌的接近提示
                write (NOR "你" + (random(2)? "握着" : "手里") + "的洞天仙府令" + (random(2)? "越来越热" : "烫手得很") + "..\n" NOR);
        }
        
        if (query_temp("dongtian/zhen/costs", me)==0) {
                //if (wiz_level(me) > 5) write (HIG ">>test 恭喜!\n" NOR);
                write (HIG + (random(2)? "蓦" : "忽")  + (random(2)? "然" : "地") + (random(2)? "你" : "只见") + "眼前一" + (random(2)? "亮" : "闪") + 
                                "，大阵透出" + (random(2)? "一" : "几") + (random(2)? "丝" : "线") + "光芒，似乎看到了阵眼(enter)!\n" NOR);
                /*//有令牌自动busy，方便进去
                if ( ling && objectp(ling) ) {
                        write (NOR "你兴奋得望着里面，用力地捏着洞天仙府令忘记了移动。\n" NOR);
                        me->start_busy(5);
                }*/
                me->stop_busy();
                me->command("go enter");//避免内贼先在此解除结义，再进去break
        }


}

int valid_leave(object me, string dir)
{
        int pow, guarderpro = 0, lifetime = 0, guarderlevel = 0, npci, last, nextc, cost = query("costs/" + dir);
        object ob;
        int iskill, itmp;
        string msg;
        object room, *inv;
        int countp;
        
        if (me->is_fighting())
                return notify_fail(NOR"你还是先解决目前的敌人吧！\n"NOR);
                
        if (!playerp(me)) {
                if (query("exits/out")) me->move(query("exits/out"));
                return notify_fail(NOR"你不是玩家！\n"NOR);
        }

                if (query("exits/" + dir)) room = get_object(query("exits/" + dir));
                if (room && objectp(room) && query("max_carry_user", room)) {//限制人数
                        inv = all_inventory(room);
                        if( sizeof(inv) > 0 ) {
                foreach( object ob3 in inv ) {
                        if ( playerp(ob3) ) countp ++;
                }
                }

                if(query("max_carry_user", room) < countp + 1 && wiz_level(me) < 5) {
                                me->start_busy(1+random(2));
                                return notify_fail(NOR"你发现对面的人太多了，你挤不过去。\n"NOR);
                }
                }

        if (undefinedp(cost)) {//非迷宫出口
                if (dir=="enter") {//如果是enter，并且query 0，方可入
                        if (query_temp("dongtian/zhen/costs", me)!=0) {
                                me->start_busy(1+random(2));
                                return notify_fail(NOR + dtname + "的府门看着似在眼前，却咫尺天涯，你始终无法靠近。\n"NOR);
                        }
                        msg = YEL "\n$N" + (random(2)? "冷静" : "沉着") + "地" + (random(2)? "移步" : "轻轻") + "往阵眼走去" + (random(2)? ".." : "...") + "\n\n" NOR;
                        message_vision(append_color(msg, YEL), me);
                }
                delete_temp("dongtian/zhen", me);
                return ::valid_leave(me, dir);
        }
                
        last = abs(query_temp("dongtian/zhen/costs", me));
        set_temp("dongtian/zhen/last", last, me);
        if (wiz_level(me) > 5) write (sprintf(HIK ">>test %d->" NOR, query_temp("dongtian/zhen/costs", me)));
        addn_temp("dongtian/zhen/costs", cost, me);
        if (wiz_level(me) > 5) write (sprintf(HIK "%d\n" NOR, query_temp("dongtian/zhen/costs", me)));
        nextc = abs(query_temp("dongtian/zhen/costs", me));
        set_temp("dongtian/zhen/nextc", nextc, me);
        
        lifetime = query("guarder_lifetime");
        guarderlevel = query("guarder_level");
        guarderpro = query("guarder_pro");

        if (!guarderpro) guarderpro = 0;
        guarderpro = 100 - guarderpro;
        if (guarderpro < 30) guarderpro = 30;
        if (random(guarderpro)<10 && !query("env/invisible", me)) {
                itmp = have_ling(me);
                if (wiz_level(me) > 5) write (sprintf(HIK ">>test itmp:%d\n" NOR, itmp));
                if ( !itmp || !dest_ling(me, random(itmp*3+1)) ) {
                
                        npci = 9 - last / (STEP_RND / 13);
                        if (npci < 2) npci = 2;
                        if (npci > 9) npci = 9;
                        pow = 11 - npci;
                        if (nextc < 20) pow = 0;
                        message_vision(CYN "青烟弥漫中，现出" + chinese_number(npci) + "个影子将$N团团围住...\n" NOR, me);
                        while (npci--) {
                                ob = new(__DIR__"npc/guarder");
                                set("guarder_level", guarderlevel, ob);
                                set("nflee", time() + 30 + random(30) + lifetime, ob);
                                ob->do_copyskill();
                                ob->move(this_object()); 
                                set("name", dtname + query("name", ob), ob);
                                //ob->set_leader(me);
                                set("enemy_player", me, ob);
                                ob->stop_busy();
                        ob->command("get all");
                        ob->stop_busy();
                        if (!pow || !random(pow)) ob->command("exert powerup");
                        ob->stop_busy();
                        if (!pow || !random(pow)) ob->command("exert shield");
                        ob->stop_busy();
                        if (!pow || !random(pow)) ob->command("exert zu");
                        ob->stop_busy();
                                ob->kill_ob(me);
                }
                return notify_fail(CYN"你被傀儡人挡住了去路。\n"NOR);
                
                }
        }
        
        iskill = (int)me->query_skill("array", 1);
        iskill += (int)me->query_skill("qimen-wuxing", 1) /3;

                if (random(iskill) > (900-query("int",me)*5)) {
                        msg = NOR "你默数奇门阵法口诀，感觉步伐" NOR;
                        if (abs(cost)>3) msg += "太大。\n";
                        else if (abs(cost)>2) msg += "较大。\n";
                        else if (abs(cost)>1) msg += "适中。\n";
                        else if (abs(cost)>0) msg += "谨慎。\n";
                        else msg += "错乱。\n";
                        write (NOR + msg + NOR);
                }
        
                if (nextc<20) {
                        if (random(iskill) > 1000 -query("int",me)*10) write (NOR "你掐指一算，洞天入口当在二十步之内..\n" NOR);
                }
                else if (nextc<50) {
                        if (random(iskill) > 800 -query("int",me)*8) write (NOR "你掐指一算，洞天入口当在五十步之内..\n" NOR);
                }
                else if (nextc<100) {
                        if (random(iskill) > 600 -query("int",me)*6) write (NOR "你掐指一算，洞天入口当在一百步之内..\n" NOR);
                }
                else if (nextc<200) {
                        if (random(iskill) > 400 -query("int",me)*4) write (NOR "你掐指一算，洞天入口当在两百步之内..\n" NOR);
                }
                else if (nextc<300) {
                        if (random(iskill) > 300 -query("int",me)*2) write (NOR "你掐指一算，洞天入口当在三百步之内..\n" NOR);
                }
                else if (nextc<400) {
                        if (random(iskill) > 200) write (NOR "你掐指一算，洞天入口当在四百步之内..\n" NOR);
                }
                else if (nextc<500) {
                        if (random(iskill) > 100) write (NOR "你掐指一算，洞天入口当在五百步之内..\n" NOR);
                } else if ((nextc % 100) < 5) {//加入此段只为降低难度...
                        if (random(5)) write (NOR "你在一棵树上看到前人刻下的数字：ｘｘ百米..\n" NOR);
                        if (query_temp("dongtian/zhen/treeflag", me)) {
                                if (query_temp("dongtian/zhen/treeflag", me) >= nextc) {
                                        me->command("tanqi");
                                } else {
                                        me->command("spank");
                                }
                        }
                        set_temp("dongtian/zhen/treeflag", nextc, me);
                }
                
        return ::valid_leave(me, dir);
}





