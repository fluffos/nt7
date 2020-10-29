// This program is a part of NITAN MudLIB  
// redl 2015/5
#include <ansi.h>  
#include <room.h>  
inherit "/u/redl/teleport/normal.c";  
#define DEBUG(msg)	if (find_player("lonely"))\
			tell_object(find_player("lonely"), msg)

int clean_up() { return 1;}
void create()
{
        set("short","十八牛人阵");
        set("long", @LONG
这里是个山洞，乌漆抹黑的伸手不见五指。你一脚踩进中间的一
个大坑里，坑里散发着阵阵恶臭，直欲叫人掩鼻逃离这里。坑边隐约
蹲着几十条人影，对着你嘿嘿奸笑。
LONG );
        set("outdoors", "yangzhou");
        set("exits",([ /* sizeof() == 1 */
            "out"  : "/u/redl/teleport/teleport",
        ]));

        set("no_rideto", 1);
        set("no_flyto", 1);
        set("no_protect", 1); 
        set("no_fly", 1);
        set("no_sleep_room", 1); 
        set("no_magic", 1); 

        set("no_user_yanjiu",1);
        set("max_carry_user" ,8);
        set("max_carry_exit" ,"out");

        setup();
        
        set_heart_beat(11);
}

int get_score(object ob) 
{ 
        int tlvl,i,score; 
        string *ski; 
        mapping skills; 
        reset_eval_cost(); 
        skills = ob->query_skills(); 
        if (!sizeof(skills)) return 1; 
        ski  = keys(skills); 
        for(i = 0; i<sizeof(ski); i++) { 
                tlvl += skills[ski[i]]; 
        }  // count total skill levels 
        score = tlvl/1; 
        score+=query("max_neili", ob)/1; 
        score += ob->query_str() + ob->query_int() + ob->query_dex() + ob->query_con(); 
        score+=query("combat_exp", ob)/10+query("reborn/times", ob)*1000000000; 
        return score; 
} 

int top_list(object ob1, object ob2) 
{ 
        int score1,score2; 
        score1 = get_score(ob1); 
        score2 = get_score(ob2); 
        return score2 - score1; 
} 

void chktop()
{
        object *list,*ob; 
        if (query("chktop_time") > time()) return;
        set("chktop_time", time()+ 7200);
        ob = filter_array(users(), (: playerp($1) && living($1) && !wizardp($1) :)); 
        list = sort_array(ob, (: top_list :)); 
        set("toplist", list);
}

int valid_leave(object me, string dir)
{
        if (!interactive(me) || !playerp(me)) return 0;
        return ::valid_leave(me, dir);
}

void start_18zhen()
{
        object room, ob, niu, *obs;
        int i, max = query("18zhen/nump");
        int tmp;

        obs = query("toplist");
        if (!obs) return;
       
        
        for (i = 0; i < max; i++) {
        
             if((18-i)>sizeof(obs)) break;
        
                ob = new (__DIR__"npc/niuren");
                               
                if (ob->do_copy(obs[18-i])){
                        set("in_zhen", 1, ob);
                        ob->move(this_object());
                        message_vision(append_color("$N哼地一声，跳进坑里把你团团围住。\n", CYN), ob);
                        if (!random(10)) {
                                niu = new (__DIR__"npc/qingniu");
                                niu->move(environment(ob));
                                niu->set_leader(ob); 
                                set("title", NOR + ob->name(1) + "的" + NOR, niu);
                        }
                } else {
                        destruct(ob);
                }
//              ob->kill_ob(enemies);
        }
}

void start_hgg()
{
        int idx, count = 0;
        string msg, *list=({});
        object room, ob, niu, *obs;
        
        if (random(8)) return;
        obs = query("toplist");
        if (!obs) return;
        if(!sizeof(obs)) return;
        niu = query("hgg/niu");
        if (niu && objectp(niu)) return;
        room = load_object("/d/changan/hanguguan");
        niu = new (__DIR__"npc/qingniu2");
        set("hgg/niu", niu);
        niu->move(room);
        for (int i=40;i>0;i--) {
                if (!random(3) && count<4) {
                        ob = new (__DIR__"npc/niuren");
                        if (ob->do_copy(obs[i])){
                                set("in_hgg", 1, ob);
                                ob->move(environment(niu));
                                ob->set_leader(niu); 
                                niu->add_team_member(ob);
                                list += ({ob->name(0)});
                                count++;
                        } else {
                                destruct(ob);
                        }
                }
        }
        CHANNEL_D->channel_broadcast("rumor", "听说" + implode(list, "、") + "等人追随老子西出函谷关。");
        niu->start_move();
}

void start_pkd()
{
        int idx;
        object niu, ob, *obs;
        addn("pkd/nump", -1);
        idx = query("pkd/nump");
        obs = query("toplist");
       if(idx<=0) return;
       if(idx>sizeof(idx)) return;
       	
       
        ob = new (__DIR__"npc/niuren");
        set("in_pkd", 1, ob);
        if (ob->do_copy(obs[idx])) {
                set("lifetime", time() + 1800, ob);
                ob->move("/d/pk/turen" + (string)(1 + random(12)));
                if (!random(5)) {
                        niu = new (__DIR__"npc/qingniu");
                        niu->move(environment(ob));
                        niu->set_leader(ob); 
                        set("title", NOR + ob->name(1) + "的" + NOR, niu);
                }
                CHANNEL_D->channel_broadcast("rumor", "比赛精灵：牛人" + ob->name(1) + "进入屠人场。" );
        } else {
                destruct(ob);
        }
}

void start_zhen()
{
        object niu, ob, *obs;
        
        obs = query("toplist");
        if (!obs) return;
        if (random(12)) return;
        if (query("18zhen/start")) return;
        
               if (query("18zhen/time") < time()) {
                        set("18zhen/time", time() + 3600 * 6 + random(3600 * 4));
                        set("18zhen/start", 1);
                }       
    CHANNEL_D->channel_broadcast("rumor", "听说有小撮不良中年人纠结在一起，布下了" + this_object()->short() + "(测试版)寻衅滋事。" );            
}

void clear_here()
{
        object ob, *obs;
        obs = filter_array(all_inventory(this_object()),  (: !userp($1) :));
        if (!obs || !sizeof(obs)) return;
        tell_room(this_object(), NOR "一阵阴风袭过，地上的狼藉化为了飞灰。\n" NOR);
        foreach (ob in obs) {
                destruct(ob);
        }
}

void heart_beat()
{
        object *obs;
                
                chktop();
                
              
                if (query("18zhen/start")) { 
                        if (query("18zhen/nump") < 18) {
                                                obs = filter_array(all_inventory(this_object()),  (: $1->is_niuren() :));
                                                //DEBUG_CHANNEL(sizeof(obs));
                                                if (!obs || sizeof(obs)<1) {
                                        addn("18zhen/nump", 3);
                                        start_18zhen();
                                        //todo:金牛，金牛免疫call die，变态hp。 
                                        //只要金牛不死，牛逼就闪闪发光, damage几率减半*n次，间或恢复，call die大大豁免。 
                                        //金牛一死，牛人很容易被call die
                                }
                        } else {
                                obs = filter_array(all_inventory(this_object()),  (: $1->is_niuren() :));
                                if (!obs || sizeof(obs)<1) {
                                        delete("18zhen/nump");
                                        delete("18zhen/start");
                                        //todo:公告天下破阵成功
                                        call_out("clear_here", 120);
                                }
                        }
                }
                
                if (query("pkd/nump") > 0) {
                        start_pkd();
                }
                        
       
}

void set_pkd()
{
        set("pkd/nump", 30);
}

void set23()
{
        start_hgg();
        start_zhen();
}

