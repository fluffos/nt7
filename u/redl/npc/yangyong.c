// This program is a part of NITAN MudLIB 
// redl 2013/8
// 5%赌神赌圣同时发作

#include <ansi.h>
#define CHANL_NAME "auc"
#define CHARM_BASEFILE "/clone/goods/tianshi-charm"
#define DEBUG 0
#define BET_ME 1        //暂且不开放，惩罚没有计算好。而且气氛不友好

inherit NPC;

int a_amount = 0, a_n1, a_n2, b_n1, b_n2, itmp, slv, sexp, spot, smar, sper;
string a_file, a_id, b_id, a_name, b_name, ob_name;
object usra, usrb;

void imp_sk(object me)
{
        if (!random(5)) {
                if (!random(3)) {
                        if (me->query_skillo("du-shen", 1) < 1000) me->improve_skill("du-shen", 200 + 2 * query("level", me)); 
                } else {
                        if (me->query_skillo("du-sheng", 1) < 1000) me->improve_skill("du-sheng", 200 + 2 * query("level", me)); 
                }
        }
}

int query_ln(object me)
{
        int tim = query("yangyong/learn/time", me);
        int num = query("yangyong/learn/num", me);
        
        if (undefinedp(tim) || !tim || tim!=time() / 86400) {
                tim = time() / 86400;
                num = 0;
                set("yangyong/learn/time", tim, me);
                set("yangyong/learn/num", num, me);
        }
        return num;
}

void add_ln(object me)
{
        addn("yangyong/learn/num", 1, me);
        tell_object(me, NOR + "你今天赌博" + chinese_number(query("yangyong/learn/num", me)) + "次了。\n" + NOR);
}

int random2 (int i)
{
        return (random(i)+uptime()) % i;
}

int rdm()
{
        object me, ene;
        object room = environment();
        int lv1, lv2, stp = query("stp_current");
        
        if (stp && usra && usrb) {
                if (stp==1) {
                        me = usra;
                        ene = usrb;
                } else if (stp==2) {
                        me = usrb;
                        ene = usra;
                } else if (stp==3) {
                        me = usra;
                        ene = usrb;
                } else if (stp==4) {
                        me = usrb;
                        ene = usra;
                } 
                
                if (stp==1 || stp==2) {
                        lv1 = me->query_skillo("du-sheng", 1);
                        lv2 = ene->query_skillo("du-sheng", 1);
                        if (lv1 && !random(4)) {
                                tell_room(room, NOR + CYN + query("name", me) + NOR + CYN + "桀桀桀地冒出几声阴笑，\n然后慢慢吐出口气道：赌～～啊～～～\n" + NOR);
                                if (random(lv2*3) > lv1) {
                                        tell_room(room, NOR + CYN + query("name", ene) + NOR + CYN + "中食指轻揉双太阳穴，猛地睁大眼睛冲着" + query("name", me) + NOR + CYN + "一盯。\n" + NOR);
                                        tell_room(room, NOR + CYN + query("name", me) + NOR + CYN + "噗地涌上一口鲜血，又强忍着内伤吞了回去。\n" + NOR);
                                        return random2(6);
                                } else {
                                        tell_room(room, NOR + CYN + query("name", me) + NOR + CYN + "继续怪笑道：～啊～～～～圣～～\n" + NOR);
                                        return 6;
                                }
                        }
                } else if (stp==3 || stp==4) {
                        lv1 = me->query_skillo("du-shen", 1);
                        lv2 = ene->query_skillo("du-shen", 1);
                        if (lv1 && !random(5)) {
                                tell_room(room, NOR + CYN + query("name", me) + NOR + CYN + "悠闲地嚼着巧克力，\n手指上的戒指却偷偷对着骰子一晃...\n" + NOR);
                                if (random(lv2*3) > lv1) {
                                        tell_room(room, NOR + CYN + query("name", ene) + NOR + CYN + "皱皱眉，拿起嘴里衔着的大雪茄，对" + query("name", me) + NOR + CYN + "劈脸一喷。\n" + NOR);
                                        tell_room(room, NOR + CYN + query("name", me) + NOR + CYN + "被呛得咳嗽不止，气急指着" + query("name", ene) + NOR + CYN + "道：你～～\n" + NOR);
                                        return random2(6);
                                } else {
                                        tell_room(room, NOR + CYN + query("name", me) + NOR + CYN + "脸上露出赌神一样的招牌微笑。\n" + NOR);
                                        if (stp==3) return a_n1;
                                        if (stp==4) return b_n1;
                                }
                        }
                }
        }
        
        return random2(6) + 1;
}

void display_bet(int i, int j)
{
        string str;
        object room = environment();
        switch (i)
        {
        case 1:
                str = ((j) ? RED : HIW) + 
"┌───┐\n"+
"│　　　│\n"+
"│　●　│\n"+
"│　　　│\n"+
"└───┘\n" + NOR;
                break;
        case 2:
                str = ((j) ? RED : HIW) + 
"┌───┐\n"+
"│　　　│\n"+
"│●　●│\n"+
"│　　　│\n"+
"└───┘\n" + NOR;
                break;
        case 3:
                str = ((j) ? RED : HIW) + 
"┌───┐\n"+
"│●　　│\n"+
"│　●　│\n"+
"│　　●│\n"+
"└───┘\n" + NOR;
                break;
        case 4:
                str = ((j) ? RED : HIW) + 
"┌───┐\n"+
"│●　●│\n"+
"│　　　│\n"+
"│●　●│\n"+
"└───┘\n" + NOR;
                break;
        case 5:
                str = ((j) ? RED : HIW) + 
"┌───┐\n"+
"│●　●│\n"+
"│　●　│\n"+
"│●　●│\n"+
"└───┘\n" + NOR;
                break;
        case 6:
                str = ((j) ? RED : HIW) + 
"┌───┐\n"+
"│●　●│\n"+
"│●　●│\n"+
"│●　●│\n"+
"└───┘\n" + NOR;
                break;
        }
        tell_room(room,str + "(" + (string)i + ")点\n" + NOR);
}

void do_return()
{
        object objb, pobj;
        
        remove_call_out("do_return");
        if (a_id && b_id)
        {
                if (a_id!="" && b_id!="" && a_file!="me") return;
        }
        
        if (a_file=="me") {
            pobj = find_player(a_id);
                if (pobj)
                {
                                pobj->stop_busy();
               
                                        set_temp("yangyong/time_start", time() - 20, pobj);
                }
                message_vision("$N不耐烦地说：" + a_name + "，都两分钟过去了也没人来赌，你这次的小命算是保住了。\n", this_object(), pobj);
        }
        else {
                objb = new(a_file);
            pobj = find_player(a_id);
                itmp = objb->query_amount();
                if (pobj)
                {
                                pobj->stop_busy();
                        if( !itmp )
                        {
                        objb->move(pobj);
                        }
                        else
                        {
                        objb->set_amount(a_amount);
                        objb->move(pobj);
                        }
                
                                        set_temp("yangyong/time_start", time() - 20, pobj);
                }
                message_vision("$N不耐烦地说：" + a_name + "，都两分钟过去了也没人来赌，" + ob_name + NOR + "还给你。\n", this_object(), pobj);
        }
        
        log_file("static/yangyong", sprintf("  -%s(%s)获得了退还。\n",  a_name, a_id));
        a_amount = 0;
        a_id = b_id = "";
}

void do_end(string id)
{
        object objb, pobj;

        remove_call_out("do_return");
        objb = new(a_file);
        pobj = find_player(id);
        itmp = objb->query_amount();
        if (pobj)
        {
                if( !itmp )
                {
                        objb->move(pobj);
                        new(a_file)->move(pobj);
                }
                else
                {
                        objb->set_amount(a_amount * 2);
                        objb->move(pobj);
                }
        }
}

void do_kill(object target, object me)
{
        mapping ob; 
        object *obs;
        int icharm = 0;
        
        //暂时移除所有的天师符
        obs = all_inventory(target); 
                if (sizeof(obs) > 0) 
                { 
                        obs = obs[0..<1]; 
                        foreach (ob in obs) {
                                if (base_name(ob)==CHARM_BASEFILE) {
                                        destruct(ob); 
                                        icharm += 1;
                                }
                        }
                } 
        
        for(int i = a_amount; i > 0; i--) {     
                set_temp("die_reason", "因为赌命输给" + query("name",me) + "而亡", target);
                target->die();
                target->reincarnate();
                target->move(environment(me));
                addn("combat_exp", sexp, me);
                addn("potential", spot, me);
                addn("experience", smar, me);
                CHANNEL_D->channel_broadcast(CHANL_NAME, NOR + query("name", me) + NOR + "从" + query("name", target) + NOR + "的尸体上获得了" + 
                        "经验:" + sexp + "，" + 
                        "潜能:" + spot + "，" + 
                        "体会:" + smar + "。\n" + NOR);
                log_file("static/yangyong", sprintf("  -经验%d、潜能%d、体会%d。\n",  sexp, spot, smar));
                sexp /= 2;
                spot /= 2;
                smar /= 2;
        }
        
        for(int j = icharm; j > 0; j--) {       
                new(CHARM_BASEFILE)->move(target);
        }       
}

int do_start(int step)
{
        string jgmsg1, jgmsg2;
        usra->start_busy(999);
        usrb->start_busy(999);
        remove_call_out("do_start");
        switch(step)
        {
                case 0:
                                message_vision("$N大声道：掷骰子现在开始。\n", this_object());
                                                                if (a_file=="me") {
                                                                        sper = 20;//奖励等于两者之和，除以20倍。不怕大米喂养，因为无法保证主id就一定会赢
                                                                        slv = abs((query("level",usra)) - (query("level",usrb)));//双方的等级差，越大奖励越低
                                                                        if (DEBUG) CHANNEL_D->channel_broadcast("wiz", NOR + "等级差:" + slv + "\n" + NOR);
                                                                        if ( (query("level",usra) / 10) < slv || (query("level",usrb) / 10) < slv ) sper *= 2;//再除以2
                                                                        if ( (query("level",usra) / 5) < slv || (query("level",usrb) / 5) < slv ) sper *= 2;//再除以2
                                                                        if ( (query("level",usra) / 2) < slv || (query("level",usrb) / 2) < slv ) sper *= 128;
                                                                        sexp = (query("combat_exp",usra));
                                                        spot = (query("potential", usra)-query("learned_points", usra));
                                                        smar = (query("experience", usra)-query("learned_experience", usra));
                                                                        sexp += (query("combat_exp",usrb));
                                                        spot += (query("potential", usrb)-query("learned_points", usrb));
                                                        smar += (query("experience", usrb)-query("learned_experience", usrb));
                                                        sexp /= sper;
                                                        spot /= sper;
                                                        smar /= sper;
                                                                        if (DEBUG) CHANNEL_D->channel_broadcast("wiz", NOR + "奖励比例:1/" + sper + "  经验:" + sexp +  "  潜能:" + spot +  "  体会:" + smar + "\n" + NOR);
                                                                }
                                break;
                case 1:
                        tell_room(environment(), RED + a_name + NOR + "轻轻一扔，骰子滴溜溜一转：\n");
                        set("stp_current", 1);
                        display_bet(a_n1 = rdm(), 1);
                                break;
                case 2:
                        tell_room(environment(), HIW + b_name + NOR + "轻轻一扔，骰子滴溜溜一转：\n");
                        set("stp_current", 2);
                        display_bet(b_n1 = rdm(), 0);
                                break;
                case 3:
                        tell_room(environment(), RED + a_name + NOR + "对着骰子哈了口气，狠狠地一扔：\n");
                        set("stp_current", 3);
                        display_bet(a_n2 = rdm(), 1);
                                break;
                case 4:
                        tell_room(environment(), HIW + b_name + NOR + "对着骰子哈了口气，狠狠地一扔：\n");
                        set("stp_current", 4);
                        display_bet(b_n2 = rdm(), 0);
                                break;
                                default:
                                if (a_n1 == a_n2) {
                                        jgmsg1 = "一对" + chinese_number(a_n1);
                                        a_n1 = (a_n1 + a_n2) * 100;
                                }
                                else {
                                        a_n1 = a_n1 + a_n2;
                                                                             jgmsg1 = chinese_number(a_n1) + "点大";
                                }
                                        
                                if (b_n1 == b_n2) {
                                        jgmsg2 = "一对" + chinese_number(b_n1);
                                        b_n1 = (b_n1 + b_n2) * 100;
                                }
                                else  {
                                        b_n1 = b_n1 + b_n2;
                                        jgmsg2 = chinese_number(b_n1) + "点大";
                                }

                                if (a_n1 > b_n1) {
                                        message_vision("$N宣布：" + jgmsg1 + "，" + RED + a_name + NOR + "得胜。\n" + NOR, this_object());
                                        log_file("static/yangyong", sprintf("  -%s(%s)胜利。\n",  a_name, a_id));
                                        if (a_file=="me") {
                                                do_kill(usrb, usra);
                                        } 
                                        else {
                                                do_end(a_id);
                                                message_vision("$N拿出一些" + ob_name + NOR + "交给" + a_name + "。\n" + NOR, this_object());
                                                CHANNEL_D->channel_broadcast(CHANL_NAME, query("name") + NOR + "拿出一些" + ob_name + NOR + "交给获胜的" + a_name + "。\n" + NOR);
                                        }
                                        if (usra) imp_sk(usra);
                                } else if (a_n1 < b_n1) {
                                        message_vision("$N宣布：" + jgmsg2 + "，" + HIW + b_name + NOR + "得胜。\n" + NOR, this_object());
                                        log_file("static/yangyong", sprintf("  -%s(%s)胜利。\n",  b_name, b_id));
                                        if (a_file=="me") {
                                                do_kill(usra, usrb);
                                        } 
                                        else {
                                                do_end(b_id);
                                            message_vision("$N拿出一些" + ob_name + NOR + "交给" + b_name + "。\n" + NOR, this_object());
                                                CHANNEL_D->channel_broadcast(CHANL_NAME, query("name") + NOR + "拿出一些" + ob_name + NOR + "交给获胜的" + b_name + "。\n" + NOR);
                                            }
                                        if (usrb) imp_sk(usrb);
                                } else {
                                        message_vision("$N高声道：平局，重新掷骰子。\n", this_object());
                                        step = 0;
                                        break;
                                }
                                        
                                a_amount = 0;
                                a_id = b_id = "";
                                set_temp("yangyong/time_start", time(), usra);
                                set_temp("yangyong/time_start", time(), usrb);
                                                        usra->stop_busy();
                                                        usrb->stop_busy();
                                add_ln(usra);                        
                                add_ln(usrb);
                                return 1;
                }
        step += 1;
        call_out("do_start", 2, step);
        return 1;
}

int do_accept()
{
        object ob, me = this_player();
        if (a_file!="me") {
                return 0;
        }
        if (a_id != query("id", me)) {
                write("这局赌博不关你的事！\n");
                return 1;
        }
        ob = find_player(b_id);
        if (!ob || !userp(ob))  {
                write("对象已经不在游戏里了！\n");
                return 1;
        }
        if (environment(ob) != environment(me)) {
                write("该对象不在这个房间里了！\n");
                return 1;
        }
        ob->start_busy(999);
        me->command("nod " +  b_id + " 好吧，陪你玩一次。");
        
                //提醒一下观众
                CHANNEL_D->channel_broadcast(CHANL_NAME, NOR + b_name + NOR + "押上" + RED + chinese_number(a_amount) + "条命" + NOR + "奉陪。\n" + HIB
                        + "  - 等级：" + (query("level",ob)) + "\n"
                        + "  - 经验：" + (query("combat_exp",ob)) + "\n"
                        + "  - 潜能：" + (query("potential", ob)-query("learned_points", ob)) + "\n"
                        + "  - 体会：" + (query("experience", ob)-query("learned_experience", ob)) + "\n"
                        + NOR);
                                log_file("static/yangyong", sprintf("  -%s(%s)奉陪，等级%d、经验%d、潜能%d、体会%d。\n",  b_name, b_id, (query("level",ob)), (query("combat_exp",ob)), (query("potential", ob)-query("learned_points", ob)), (query("experience", ob)-query("learned_experience", ob)))); 

                                set("yangyong/time_start", time());
                                remove_call_out("do_return");
                call_out("do_start", 3, 0);

        return 1;       
}

int do_no()
{
        object me = this_player();
        if (a_file!="me") {
                return 0;
        }
        if (a_id != query("id", me)) {
                write("这局赌博不关你的事！\n");
                return 1;
        }
        if (!b_id) {
                write("没有人想和你赌博呀！\n");
                return 1;
        }
        me->command("shake 我对你没兴趣呀");
        b_id = "";
        
        return 1;
}

int do_bet(string arg)
{
        object me;
        object ob;
        object nob;
        object *inv;
        string my_id, units;
        int amount;
        int value;
        int res;
        int max_count;
        int i;
        mixed ns;

        if( !arg ) {
                return notify_fail("你要赌什么？\n");
        }
        
                if ((time() - query("yangyong/time_start")) < 30) 
        {
                write(CYN + name() + "不耐烦道：“等会儿，我忙着呢。”\n" NOR);
                return 1;
        }

        me = this_player();
       
        if(!interactive(me) || !playerp(me) || me->is_busy()) {
                return notify_fail("你正忙着呢。\n");
        }
        
        if (query_ln(me)>=30) {
                write(CYN + name() + "气愤道：“你今天都压３０次了还来？戒一戒赌吧。”\n" NOR);
                return 1;
        }
        
        if (query("online_time", me) < 43200) {
                write(CYN + name() + "不耐烦道：“你才多大点呀？毛都没长齐也想玩黄赌毒。”\n" NOR);
                return 1;
        }
                
                if ((time() - query_temp("yangyong/time_start", me)) < 35) 
        {
                write(CYN + name() + "不耐烦道：“等会儿，你才刚赌过吧？”\n" NOR);
                return 1;
        }

                if (a_id && b_id) {
                        if (a_id!="" && b_id!="") {
                                write(CYN + name() + "说道：“再等一等吧，有两个人正在玩呢。”\n" NOR);
                            return 1;
                        }
                }
       
        if( sscanf(arg, "%d %s", amount, arg) != 2 )
                // not indicate the amount of the goods
                amount = 1;

        if( amount < 1 )
        {
                write(CYN + name() + "疑惑的问道：“没见过这种赌法，你到底想赌几件呢？”\n" NOR);
                return 1;
        }


        if (arg == "me") {//赌命
                
                if (!BET_ME)
                {
                write(CYN + name() + "皱眉道：赌命暂时不开放。”\n" NOR);
                return 1;
                }

        if( amount > 10 )
        {
                write(CYN + name() + "大惊失色道：“你这也太狠了吧？我现在最多支持赌十条命。”\n" NOR);
                return 1;
        }
       
        if (a_amount) {

                        if (query("id", me)==a_id) {
                                write(CYN + name() + "嗤笑道：“自己和自己拼命，你是白痴吧？”\n" NOR);
                                return 1;
                        }
                        
                        if (a_file!="me") {
                                write(CYN + name() + "眼泪都笑出来了说：“我看" + a_name + "似乎不想和你玩命啊！”\n" NOR);
                                return 1;
                        }

                        if (amount!=a_amount) {
                                write(CYN + name() + "奸笑着说：“怎么你押的性命数目和" + a_name + "的不一致啊？”\n" NOR);
                                return 1;
                        }

                        message_vision("$N恶狠狠地大吼：我来奉陪，" + a_name + "你敢答应(accept)吗？。\n",
                                       me, this_object());

                b_id = query("id", me);
                usrb = me;
                b_name = query("name", me);
                set_temp("yangyong/time_start", time() + 25, me);

                                tell_object(find_player(a_id), HIG + name() + HIG +  "偷偷告诉你：" + b_name + HIG + "的情报... \n" + HIB
                        + "  - 等级：" + (query("level",me)) + "\n"
                        + "  - 经验：" + (query("combat_exp",me)) + "\n"
                        + "  - 潜能：" + (query("potential", me)-query("learned_points", me)) + "\n"
                        + "  - 体会：" + (query("experience", me)-query("learned_experience", me)) + "\n" + HIG
                        + "如果不想赌可以输入(no)。\n"
                        + NOR);
               
        } else {

                        message_vision("$N大声对$n说道：我要押上自己的" + chinese_number(amount) + "条命。\n",
                                       me, this_object());
                                                                       
                a_id = query("id", me);
                usra = me;
                a_name = query("name", me);
                a_amount = amount;
                a_file = "me";
                write(CYN + name() + "对你说：“现在后悔已经没用了，安心等候结果吧。”\n" NOR);
                me->start_busy(999);
                call_out("do_return", 120);
                //提醒一下观众
                CHANNEL_D->channel_broadcast(CHANL_NAME, NOR + a_name + NOR + "押上" + RED + chinese_number(a_amount) + "条命" + NOR + "在羊勇的赌档上等待挑战。\n" + HIB
                        + "  - 等级：" + (query("level",me)) + "\n"
                        + "  - 经验：" + (query("combat_exp",me)) + "\n"
                        + "  - 潜能：" + (query("potential", me)-query("learned_points", me)) + "\n"
                        + "  - 体会：" + (query("experience", me)-query("learned_experience", me)) + "\n"
                        + NOR);
                                log_file("static/yangyong", sprintf("(%s)%s(%s)在羊勇押了%d条命，等级%d、经验%d、潜能%d、体会%d。\n",  ctime(time()), a_name, a_id, a_amount, (query("level",me)), (query("combat_exp",me)), (query("potential", me)-query("learned_points", me)), (query("experience", me)-query("learned_experience", me)))); 

        }
                
                return 1;
        }
        
        ob = present(arg, me);
        if( !ob )
        {
                inv = all_inventory(me);
                for( i = 0; i < sizeof(inv); i++ )
                {
                        if( filter_color(inv[i]->name(1)) == arg )
                        {
                                ob = inv[i];
                                break;
                        }
                }
        }

        if ( !objectp(ob) )
        {
                write("你身上没有这种东西啊！\n");
                return 1;
        }

        max_count = ob->query_amount();
        if( !max_count )
        {
                // not combined object
                if( amount > 1 )
                {
                        write(ob->name() + "这种东西不能拆开来赌。\n");
                        return 1;
                }
                max_count = 1;
        } else
        {
                // is combined object
                if( amount > max_count )
                {
                        write("你身上没有这么多" + ob->name() + "。\n");
                        return 1;
                }
        }


        if( ob->is_character() )
        {
                write(CYN + name() + "惊讶道：“这东西也能赌？！”\n" NOR);
                return 1;
        }

        if( query("unique", ob)
        ||  query("no_pawn", ob)
        ||  query("replica_ob", ob) )
        {
                write(CYN + name() + "摇摇头，道：“这种东西我"
                      "不识货，不敢接。”\n" NOR);
                return 1;
        }

        if( query("no_drop", ob) ||
            (ns = query("no_sell", ob)) )
        {
                write(CYN + name() + "摇摇头，道：“这种东西我"
                      "不识货，不敢接。”\n" NOR);
                return 1;
        }

        if( query("food_supply", ob)
        ||  ob->is_liquid() )
        {
                write(CYN + name() + "不屑道：“嘿嘿，剩菜剩饭留给"
                      "您自己用吧。”\n" NOR);
                return 1;
        }

        if( query("shaolin", ob) )
        {
                write(CYN + name() + "惊道：“小的胆子很小，可"
                      "不敢赌少林庙产。”\n" NOR);
                return 1;
        }

        if( query("mingjiao", ob) )
        {
                write(CYN + name() + "忙摇头道：“小的只有一个脑袋，可"
                      "不敢赌魔教的东西。”\n" NOR);
                return 1;
        }

        if( sscanf(base_name(ob), "/data/%*s") )
        {
                write(CYN + name() + "说道：“厚道点，被绑定过的东西不能拿来骗人啊。”\n" NOR);
                return 1;
        }
        
        //"/inherit/template/armor/armor"
        if( sscanf(base_name(ob), "/inherit/template/%*s") )
        {
                write(CYN + name() + "说道：“这种东西不能赌。”\n" NOR);
                return 1;
        }


        if( query("consistence", ob) )
                value = value * query("consistence", ob) / 100;

        if( max_count > 1 )
        {
                if( query("base_value", ob) * amount / amount != query("base_value", ob) )
                {
                        write(CYN + name() + CYN "大惊失色道：这么大一笔生意？我"
                              "可不好做。\n" NOR);
                        return 1;
                }
                value = query("base_value", ob) * amount;
        }
        else
                value = query("value", ob);

        if( value < 2 ) {
                write(CYN + name() + "随手一扔，道：" + query("name", ob) +
                      CYN "一文不值！\n" NOR);
                                return 1;
        }
        
                if( query("bind_owner", ob) || query("bindable", ob) )
                {
                        write(CYN + name() + "说道：“厚道点，被绑定过的东西不能拿来骗人啊。”\n" NOR);
                        return 1;
                }
                
                if (a_amount) {
                        if (query("id", me)==a_id) {
                                write(CYN + name() + "嗤笑道：“自己和自己玩，你没发烧吧？”\n" NOR);
                                return 1;
                        }
                        
                        if (base_name(ob)!=a_file) {
                                write(CYN + name() + "奸笑着说：“怎么你拿出来的东西和对方的不一致啊？”\n" NOR);
                                return 1;
                        }

                        if (amount!=a_amount) {
                                write(CYN + name() + "奸笑着说：“怎么你拿出来的数目和对方的不一样啊？”\n" NOR);
                                return 1;
                        }
                        
                }

                if (query("base_unit", ob)) {
                        units = query("base_unit", ob);
                }
                else if (query("unit", ob)) {
                        units = query("unit", ob);
                }
                else {
                        units = "个";
                }

        message_vision("$N拿出" + chinese_number(amount) + units +
                                       query("name", ob) + "(" + query("id", ob) + ")" + "交给$n。\n",
                                       this_player(), this_object());
        
        if (a_amount) {
                b_id = query("id", me);
                usrb = me;
                b_name = query("name", me);
                                set("yangyong/time_start", time());
                                remove_call_out("do_return");
                call_out("do_start", 3, 0);
                                log_file("static/yangyong", sprintf("  -%s(%s)奉陪。\n",  b_name, b_id)); 
        } else {
                a_id = query("id", me);
                usra = me;
                a_name = query("name", me);
                a_amount = amount;
                a_file = base_name(ob);
                ob_name = query("name", ob);
                call_out("do_return", 120);
                //提醒一下观众
                CHANNEL_D->channel_broadcast(CHANL_NAME, NOR + a_name + NOR + "拿出" + chinese_number(a_amount) + units + ob_name + "(" + query("id", ob) + ")" + NOR + "在羊勇的赌档上等待挑战。\n" + NOR);
                        log_file("static/yangyong", sprintf("(%s)%s(%s)在羊勇押了%d个%s(%s)。\n",  ctime(time()), a_name, a_id, a_amount, ob_name, a_file)); 
        }
        
                if( max_count == amount ) {
                        destruct(ob);
                }
                else
                {
                        ob->add_amount(-amount);
                }
                
                write(CYN + name() + "对你说：“超重不赔，重启不赔，不准乱走，自求多福吧。”\n" NOR);
                me->start_busy(999);                
        return 1;
}




int ask_nt()
{
                int amount;
        object me = this_player();
        
                if(!interactive(me) || !playerp(me) || me->is_busy()) return notify_fail("你正忙着呢。\n");
        
        if( query("online_time", me) < 3600){
                tell_object(me,CYN + query("name") + CYN + "深情地看了你一眼说：你是新来的吧..吧...？\n"+ NOR); 
                return 1;
        }      

        amount = MEMBER_D->db_query_member(me, "money");
        
        if( amount < 102){
                tell_object(me,CYN + query("name") + CYN + "面孔扭曲地说：你账户上没有102 $NT来兑换呀！\n"+ NOR); 
                return 1;
        }
        
        if (!query_temp("yangyong/nt", me)) {
                tell_object(me,CYN + query("name") + CYN + "亲切地说：确定要兑换请再次输入<ask yang yong about NT>。\n"+ NOR); 
                set_temp("yangyong/nt", 1, me);
                return 1;
        }

                me->start_busy(2);

                amount -= 102;
        if (!MEMBER_D->db_set_member(me, "money", (amount)))
        {
                write("兑换失败，请与本站ADMIN联系！\n");
                return 1;
        }
        write(HIG + "羊勇悄悄告诉你：会员账户余额: (" + amount + ") $NT。\n" + NOR);

        new(__DIR__"obj/ntb")->move(me);
        message_vision(YEL + "$N" + NOR + YEL+ "从" + query("name") + NOR + YEL+ "手里接过一张百元泥潭币。\n" + NOR, me);        
        log_file("static/yangyong3",sprintf("%s %s 100 $NT -> 百元泥潭币, 账户余 %d $NT\n",TIME_D->replace_ctime(time()), query("id", me), amount));
       
        return 1;
}      

void create()
{
        set_name(NOR "羊勇" NOR, ({ "yang yong", "yang" }));
         set("nickname", HIK "黑心老板" NOR);
        set("long", @LONG
云南边境上走私贩毒的奸商，退出江湖后在公共聊天室附近坑人搞赌。
LONG);
        set("gender", "男性" );
        set("age", 38);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("per", 13);
        set("combat_exp", 1333000);

        set("inquiry", ([
                "nt"   : (: ask_nt :),
                "NT"   : (: ask_nt :),
                "赌博说明"     : "支持两个玩家对赌，使用<bet 数量 id名>，就可以把物品押上来。\n"+NOR,
                "兑换说明" : "如果member账户上有102 $NT，可以<ask yang yong about NT>兑换成一张百元泥潭币。\n"+NOR,
                "赌命说明"     : "支持两个玩家对赌，使用<bet 数量 me>，就可以押上几条性命，天师符在此无效。\n"+NOR,
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

}



void init()
{
        if (! interactive(this_player())) return;
        add_action("do_bet", "bet");
        add_action("do_accept", "accept");
        add_action("do_no", "no");
}



