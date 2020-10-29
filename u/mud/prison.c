// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 

#define THROWTIME 30    //基础禁闭分钟

int clean_up() { return 1;}

int do_cantsave()
{
        object me = this_player();
                tell_object(me, NOR "这是水牢里，你老实点吧。\n" NOR);
                return -1;
}

int do_action(string arg)
{
        string action = query_verb();
        object me = this_player();
        
        if (me->is_busy() && action!="stat") {
                tell_object(me, NOR "你还是忙完手头上的事情再说吧。\n" NOR);
                return -1;
        }

        if (action=="chat" || action=="rumor" || action=="ask1") {//没走出这房间就始终不能公聊
                        me->start_busy(2);
                tell_object(me, NOR "你张口欲喊，墙壁上射出几股臭水喷了你一脸。\n" NOR);
                return -1;
        }

        if (query("redlworkroom/prison/time", me) > query("online_time", me) && 
                action!="tell" && action!="reply" && action!="look"  && action!="say" && action!="stat" && action!="halt") {
                me->start_busy(2);
                tell_object(me, NOR "你胡乱扭摆身体，陷在齐腰深的水里却动不了。\n" NOR);
                return -1;
        }
        
        if (action=="tell" || action=="reply") {
                me->start_busy(60);//远处说话避免持续骚扰
        }
        
        return 0;
}

int throwing(object me, int i, string bmsg)
{
        int c, p = query("redlworkroom/prison/num", me);
        
        if (undefinedp(p) || !p) p = 0;
        
        c = (60 * i) * (5 + p) / 5;
        set("redlworkroom/prison/bmsg", bmsg, me);
        set("redlworkroom/prison/ti", i, me);
        set("redlworkroom/prison/time", query("online_time", me) + c , me);
        set("redlworkroom/prison/num", p + 1, me);
        
        message_vision(append_color(NOR + YEL + "虚空中穿过来一只大如山岳的巨掌，对着$N" + NOR + YEL + "拦腰一捞，再缩回去就此不见了。\n" + NOR, YEL), me);
        me->move(this_object());
        return 1;
}

int delay_msg(string msg, object me)
{
        message_vision(msg, me);
        return 1;
}

int is_owner(object me) { 
        return ( query("id", me) == "redl" || 
                wiz_level(me) > 6 || 
                query("couple/couple_id", me) == "redl" || 
                query("redlworkroom/prison/immune", me) ) ? 1 : 0; 
}

int do_fr(string arg)
{
        object me, where;
        
        if (!arg) return notify_fail(NOR "你要输入一个在线的玩家id才行。\n"NOR );
        me = find_player(arg);
        if (!me || !playerp(me)) return notify_fail(NOR "没有这个玩家在线。\n"NOR );
        where = environment(me);
        if ( (this_object() != where) || (query("in_prison", me) !=base_name(this_object())) ) return notify_fail(NOR "这个玩家没有在这里坐牢。\n"NOR );
        
                message_vision(append_color(NOR YEL "$N" NOR YEL "耳边响起$n的声音道：“你可以出去了”。\n" NOR, YEL), me, this_player());
                delete("redlworkroom/prison/time", me);
                me->stop_busy();
                me->move("/d/city/kedian4");
                message_vision(append_color(NOR YEL "$N" NOR YEL "狼狈不堪地从" + query("short") + NOR + YEL + "跑了出来。\n" NOR, YEL), me);
                tell_object(me, NOR + HIC + "一个声音告诉你道；" + HIG + "以后别再" + query("redlworkroom/prison/bmsg", me) + "了。\n" + NOR);
                set("startroom", "/d/city/wumiao", me);
                delete("in_prison", me);
                me->save();

        write("ok.\n");
        return 1;
}

int do_clr(string arg)
{
        object me;
        
        if (!arg) return notify_fail(NOR "你要输入一个在线的玩家id才行。\n"NOR );
        me = find_player(arg);
        if (!me || !playerp(me)) return notify_fail(NOR "没有这个玩家在线。\n"NOR );
        
                tell_object(me, NOR + "你的犯罪记录被清除了。\n" + NOR);
                delete("redlworkroom/prison/num", me);
                me->save();

        write("ok.\n");
        return 1;
}

int do_imm(string arg)
{
        object me;
        
        if (!arg) return notify_fail(NOR "你要输入一个在线的玩家id才行。\n"NOR );
        me = find_player(arg);
        if (!me || !playerp(me)) return notify_fail(NOR "没有这个玩家在线。\n"NOR );
        
                tell_object(me, NOR + "你被赋予了在" + query("short") + NOR + "的豁免权。\n" + NOR);
                set("redlworkroom/prison/immune", 1, me);
                me->save();

        write("ok.\n");
        return 1;
}

void init()
{
        object *prisoners, me = this_player();
        string cti;
        
        add_action("do_cantsave", ({
                "push", "save", "get", "uget", "drop", "quit", 
                "home", "exit", "recall", "team", "chatroom", 
                "rideto", "array", "battle", "accept", "fbattle"}));

        if ( is_owner(me) ) {
                add_action("do_fr", "fr");
                add_action("do_clr", "clr");
                add_action("do_imm", "imm");
                write("你可以：\n释放犯人<fr sb>\n犯罪次数清零<clr sb>\n给予今后的豁免<imm sb>\n");
                return; 
        }
        if (query("redlworkroom/prison/time", me)) {
                       delete("doing", me);  
                    me->stop_busy(); 
                    me->command("halt"); 
                me->start_busy(30);
                prisoners = query("prisonerlist");
                if (undefinedp(prisoners) || !prisoners || !sizeof(prisoners))
                        set("prisonerlist",  ({me}));
                else if (member_array(me, prisoners) < 0)
                        set("prisonerlist",  prisoners + ({me}));
                cti = chinese_number(abs((query("redlworkroom/prison/time", me)-query("online_time", me))) / 60) + "分钟";
                if (query("startroom", me)!=base_name(this_object())) {
                        message_system(filter_color(query("name", me), 1) + query("redlworkroom/prison/bmsg", me) + "(犯禁" + chinese_number(query("redlworkroom/prison/num", me)) + "次)。\n" + NOR);
                        CHANNEL_D->channel_broadcast("rumor", NOR + MAG + "听说" + filter_color(query("name", me), 1) + "被抓进" + query("short") + NOR + MAG + "禁闭" + cti + "。\n" + NOR);
                }
                call_out("delay_msg", 2, append_color(NOR + YEL + "$N" + NOR + YEL + "像只死狗样被扔了进来，一个阴森的声音说道：" +  cti + "后自己出去。\n" + NOR, YEL), me);
                set("startroom", base_name(this_object()), me);
                set("in_prison", base_name(this_object()), me);
                me->save();
                add_action("do_action", "");
        }
        
}

void create()
{
        set("short", NOR HIC "化乐" HIK "水牢" NOR);
        set("long", 
"这是化乐天里黑幽幽的水牢，一米多深的水浸满了整个房间，臭不可闻。\n"
);
                set("exits",([ /* sizeof() == 1 */
                        "east" : __DIR__"houdian",
                ]));

        set("no_dazuo",1);
        set("no_kill",1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
                set("no_magic", 1); 
        set("no_sleep_room", 1); 
        set("valid_startroom", 1);
        
        set_heart_beat(15);

        setup();
}

int valid_leave(object me, string dir)
{
        if (query("redlworkroom/prison/time", me) && dir == "east") {
                message_vision(append_color(NOR YEL "$N" NOR YEL "仿佛想起什么提示，狼狈不堪地跑出了水牢。\n" NOR, YEL), me);
                delete("redlworkroom/prison/time", me);
                me->start_busy(3);
                me->move("/d/city/kedian4");
                message_vision(append_color(NOR YEL "$N" NOR YEL "狼狈不堪地从" + query("short") + NOR + YEL + "跑了出来。\n" NOR, YEL), me);
                tell_object(me, NOR + HIC + "一个声音告诉你道；" + HIG + "以后别再" + query("redlworkroom/prison/bmsg", me) + "了。\n" + NOR);
                set("startroom", "/d/city/wumiao", me);
                delete("in_prison", me);
                me->save();
                return -1;
        }
        delete("in_prison", me);
        return ::valid_leave(me, dir);
}

void heart_beat()
{
                object prisoner, *prisoners, where;
                int ti;
                
                prisoners = query("prisonerlist");
                if (!undefinedp(prisoners) && prisoners && sizeof(prisoners)) {
                        foreach (prisoner in prisoners) {
                                if (!prisoner || !objectp(where=environment(prisoner)) || !query("redlworkroom/prison/time", prisoner)) {
                                                prisoners -= ({prisoner});
                                                continue;
                                }
                                if (this_object() != where) {
                                        ti = query("redlworkroom/prison/ti", prisoner);
                                        if (ti < 1) ti = 1;
                                        throwing(prisoner, ti, "越狱");
                                }
                        }
                        set("prisonerlist",  prisoners);
                }
}

void throw_flood(object me, object ob)
{
        log_file( "static/throwf", sprintf("%s  %s->%s\n",TIME_D->replace_ctime(time()), query("id", me), query("id", ob) )); 
        throwing(ob, THROWTIME * 2, "故意刷屏");        
}

mapping *fmsk = ({
                (["id":"huajia-su",
                                "limit":1280,
                        "tname":"化甲术",
                        "fam":"全真教"
                        ]),
                (["id":"jingxin",
                                "limit":1280,
                        "tname":"静心",
                        "fam":"峨嵋派"
                        ]),
                (["id":"jianyi",
                                "limit":1280,
                        "tname":"剑意",
                        "fam":"华山派"
                        ]),
                (["id":"wudu-jing",
                                "limit":1280,
                        "tname":"五毒阱",
                        "fam":"五毒教"
                        ]),
                (["id":"bingchan-gong",
                                "limit":1280,
                        "tname":"冰蚕功",
                        "fam":"星宿派"
                        ]),
                     (["id":"freezing-force", 
                             "tname":"冰蚕寒功", 
                             "fam":"星宿派" 
                             ]), 
                (["id":"tianwei-zhengqi",
                                "limit":1280,
                        "tname":"天威正气",
                        "fam":"武当派"
                        ]),
                (["id":"fanlao-huantong",
                                "limit":1280,
                        "tname":"返老还童功",
                        "fam":"灵鹫宫"
                        ]),
                (["id":"taishang-wangqing",
                                "limit":1280,
                        "tname":"太上忘情",
                        "fam":"古墓派"
                        ]),
                (["id":"xiaoyao-you",
                                "limit":1280,
                        "tname":"逍遥游",
                        "fam":"逍遥派"
                        ]),
                (["id":"qimen-xuanshu",
                                "limit":1280,
                        "tname":"奇门玄术",
                        "fam":"桃花岛"
                        ]),
                (["id":"xueying-dafa",
                                "limit":1280,
                        "tname":"血影大法",
                        "fam":"密宗"
                        ]),
                (["id":"mizong-zhenyan",
                                "limit":1280,
                        "tname":"密宗真言",
                        "fam":"密宗"
                        ]),
                (["id":"bixue-danxin",
                                "limit":1280,
                        "tname":"碧血丹心",
                        "fam":"丐帮"
                        ]),
                (["id":"daojian-xiaotianwai",
                                "limit":1280,
                        "tname":"刀剑啸天外",
                        "fam":"关外胡家"
                        ]),
                (["id":"lunhui",
                                "limit":1280,
                        "tname":"轮回",
                        "fam":"少林派"
                        ]),
                (["id":"huitong-tianxia",
                                "limit":1280,
                        "tname":"慧通天下",
                        "fam":"慕容世家"
                        ]),
                (["id":"guangming-jing",
                                "limit":1280,
                        "tname":"大云光明经",
                        "fam":"明教"
                        ]),
                (["id":"jinchan-tunyue",
                                "limit":1280,
                        "tname":"金蟾吞月",
                        "fam":"欧阳世家"
                        ]),
                (["id":"qimai-liuzhuan",
                                "limit":1280,
                        "tname":"气脉流转",
                        "fam":"段氏皇族"
                        ]),
                (["id":"motun-tianxia",
                                "limit":1280,
                        "tname":"魔吞天下",
                        "fam":"魔教"
                        ]),
                (["id":"luoxian-jue",
                                "limit":1280,
                        "tname":"落仙诀",
                        "fam":"唐门世家"
                        ]),
                (["id":"richu-dongfang",
                                "limit":1280,
                        "tname":"日出东方",
                        "fam":"日月神教"
                        ]),
        });

int chk1()
{
        object *players;
        object *users;
                int no_cg, idx = random(sizeof(fmsk));
                string *cgsks, str = fmsk[idx]["id"];
                mapping cg_data;
                
        if (! str)
                return notify_fail("你要统计什么技能？\n");
        if (file_size("/kungfu/skill/" + str + ".c") == -1)
                return notify_fail("没有这个技能存在！\n");                
        users = users();
        players = ({});
        foreach (object player in users)  {
                if (player->query_skill(str, 1)) {
                        players += ({ player });
                }
        }
                //write(HIY + "统计"+fmsk[idx]["tname"]+":\n" + NOR);
        foreach (object player in players) {
                if (player->query_skill(str, 1)) {
                        /*write(sprintf(HIC "%-21s年龄：%-10d所属门派：%-16s等级：%-10d\n" NOR,
                                      player->name()+"("+query("id", player)+")",

                                      query("age", player),
                                      query("family/family_name", player),
                                      player->query_skill(str, 1)));*/
                       no_cg = 0;
                       cg_data = query("dongtian/cg_data/skills_id", player);
                       if (!cg_data || !mapp(cg_data) || !sizeof(cg_data)) {
                                no_cg = 1;
                       } else {
                                cgsks = keys(cg_data);
                                if (member_array(str, cgsks)==-1) {
                                        no_cg = 1;
                                }
                       }
                       if ( !is_owner(player) && 
                                (! player->is_in_prison()) &&
                                (! query("in_prison", player)) && 
                                (fmsk[idx]["fam"]!=query("family/family_name", player) && 
                                !query("betrayer/" + fmsk[idx]["fam"], player) && 
                                no_cg) ) {
                                //write(HIR + "犯禁！\n" + NOR);
                                throwing(player, THROWTIME, "偷学" + fmsk[idx]["tname"] + "(" + str + ")");
                       }               
                }
        }
        return 1;
}

int filter_skill(string sk, object me)
{
        //if (!me->can_improve_skill(sk)) return 0;
        if (SKILL_D(sk)->type() != "martial") return 0;
        return 1;
}
int chk2sgl(object player)
{
        int sklv, sklvmax, sklvmax2, r;
        string sk, skname, *ks;
        string fsk;

                        if (!player || !objectp(player)) return 0;
                if (!playerp(player)) return 0;
                if (query("combat_exp", player) < 5000000000) return 0;
                        if (is_owner(player)) return 0;
                        if (player->is_in_prison()) return 0;
                        if (query("in_prison", player)) return 0;
                if (!player->query_skills() || !sizeof(player->query_skills())) return 0;
                
                foreach (mapping mfsk in fmsk)  {
                                fsk = mfsk["id"];
                                if (mfsk["limit"] && 
                                        player->query_skillo(fsk,1) > mfsk["limit"]) {
                                        //write(HIY + "统计到"+player->name()+"("+query("id", player)+")的"+mfsk["tname"]+"("+fsk+")的等级超过了"+(string)mfsk["limit"]+"\n" + NOR);
                                        log_file( "static/throw_skup", player->name()+"("+query("id", player)+")的"+mfsk["tname"]+"("+fsk+")的等级超过了"+(string)mfsk["limit"]+"\n");
                                        throwing(player, THROWTIME, mfsk["tname"]+"("+fsk+")等级异常达到" + (string)player->query_skillo(fsk,1) + "级");
                                        tell_object(player, NOR BLINK HIR "\n如果有异议，msg mail redl，留下你的解释。\n确定冤情后对于被禁闭的时段，可获补偿50NT/小时。\n\n" NOR);
                                        return 1;
                                }
                        }
                
                ks = filter_array(keys(player->query_skills()), (: filter_skill :), player);
                        if (r = sizeof(ks))
                        {
                                //write(NOR + "抽检(" + player->name()+ ")\n" + NOR);
                                        r = random(r);
                                        sk = ks[r];
                                        skname = to_chinese(sk);
                                        sklv = player->query_skillo(sk,1);
                                        sklvmax = to_int(pow(to_float(pow(to_float(query("level", player))+1.0, 3.0)*10000/100), 1.0 / 3)*10) + 1;
                                        sklvmax2 = to_int(pow(to_float(query("combat_exp", player)/100), 1.0 / 3)*10) + 1;
                                        
                                        if (sklv < 2000) return 0;
                                        if (sklv < sklvmax * 13 / 10) return 0;
                                        if (sklv < sklvmax2 * 13 / 10) return 0;
                                        //write(HIY + "统计到"+player->name()+"("+query("id", player)+")的"+skname+"("+sk+")的等级"+(string)sklv+"异常\n" + NOR);
                                        log_file( "static/throw_skup", player->name()+"("+query("id", player)+")的"+skname+"("+sk+")的等级"+(string)sklv+"异常\n");
                                        throwing(player, THROWTIME, skname+"("+sk+")等级异常达到" + (string)sklv + "级");
                                        tell_object(player, NOR BLINK HIR "\n如果有异议，msg mail redl，留下你的解释。\n确定冤情后对于被禁闭的时段，可获补偿50NT/小时。\n\n" NOR);
                                        return 1;
                        }
                        
                if (query("redlworkroom/prison/atlogin", player)) {
                        addn("redlworkroom/prison/atlogin", -1, player);
                        call_out("chk2sgl", 15, player);
                }
                
        return 0;
}
int chk2()
{
        object *users;
        object player;
        int rall, pidx = 20;//抽检20人
                
        users = users();
        rall = sizeof(users);
        if (rall < pidx + 1) return 1;
        //foreach (object player in users)  {
        while (pidx>0) {
                pidx -= 1;
                player = users[random(rall)];
                if (query("redlworkroom/prison/atlogin", player)) continue;
                chk2sgl(player);
        }
        return 1;
}
int chk2_at_login(object player)
{
//      if (query("redlworkroom/prison/atlogintime", player) && query("redlworkroom/prison/atlogintime", player) > time())
//              return 1;
//      else
//              set("redlworkroom/prison/atlogintime", time() + 3600, player);
        set("redlworkroom/prison/atlogin", 4, player);
        call_out("chk2sgl", 3, player);
    return 1;
}


void check_bug_user(string arg)
{
        switch (arg) {
                case "fmsk"     :
                        chk1();
                        break;
                case "skup"             :
                        chk2();
                        break;
        }
}



