// 绝地末日·NPC: /d/suzhou/npc/xi-laifu.c  办喜宴出现的喜来福老板
// llm 99/07/09 修改2000.09

#include <ansi.h>

inherit BUNCHER;
int ask_party();
void start_party(object,object);
int do_start();
int do_serve();
void finish_party(object,object);
int give_money(object,object);
int do_kill(string);
int do_exert();
int do_steal(string);
int kick(object);

void create()
{
        set_name("喜来福",({"xi laifu","xi","laifu" }));
   set("title", "迎宾楼老板");
   set("age", 42);
   set("gender", "男性");
   set("attitude", "friendly");
   set("combat_exp", 50000);
   set_skill("unarmed", 100);
   set_skill("dodge", 100);
   set_skill("parry", 100);
   set("per", 20);

        set("inquiry", ([
                "name": "喜来福呵呵笑道：“小可名字有点福气，姓喜名来福，就是这里的老板。\n",
                "here": "喜来福摇头晃脑地说：“我们迎宾楼可是方圆几十里的名楼，办喜宴还得要来我们这里。”\n",
                "宴" : (: ask_party :),
                "喜宴" : (: ask_party :),
                "席" : (: ask_party :),
                "酒席" : (: ask_party :),
                "喜酒" : (: ask_party :),
                "酒宴" : (: ask_party :),
                "party" : (: ask_party :),
                "送礼":"喜来福呵呵笑道：“新人的礼金交给我好了，我来转交给他们！”\n",
                "礼":"喜来福呵呵笑道：“新人的礼金交给我好了，我来转交给他们！”\n",
                ]) );
   setup();
   carry_object("/d/beijing/npc/obj/hupi")->wear();
}

void init()
{
        object me=this_player();
        ::init();
        if( !query("no_fight", environment()) )
                set("no_fight", 1, environment());//将此地设为不能战斗
        if( interactive(me) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
        add_action("do_serve", "kaixi");
        add_action("do_finish", "jieshu");
        add_action("do_start", "kaishi");
        add_action("do_kill", ({"kill","fight","hit","perform","yong","ge","touxi"}));
        add_action("do_steal", "steal");
        add_action("do_exert", ({"exert","yun"}));
}

int greeting(object me)
{
        if( !me || environment(me) != environment() ) return 0;
        if( query_temp("married_party", me))//新人
                write("喜老板对你拱手道：“喜宴布置得差不多了，等客人来齐了您问我喜宴就行了！”\n");
        else if( query_temp("kick", me))//被踢的人
                write("喜来福冲你哼了一声：“不想尝尝老夫的佛山无影腿就老实点。”\n");
        else if(!query_temp("party_finish"))//喜宴未结束，吃喜酒的人
                write("喜老板点点头：“哟！您来吃喜酒呀！新人的礼金由我代收，交给我就行。”\n");
        else
                write("喜老板一拱手：“您吃好，慢走！”\n");
        return 1;
}

int accept_object(object me, object ob)
{
        int i;
        if(!query("name1")||!query("name2"))
                return notify_fail("喜来福迷惑地看看你：“我们现在没给谁办喜酒呀！你送谁的礼？”\n");
        if(query_temp("party_finish"))
                return notify_fail("喜老板呵呵一笑：“您来迟了，喜宴已经结束了，您还是直接给新人吧！”\n");
        if( !query("money_id", ob) )
             return notify_fail("喜老板皱了皱眉头：“如今早就不时兴送东西了，喝喜酒还是给现金的好！”\n");
        if( query_temp("married_party", me))//新人
                return notify_fail("喜老板一愣，又笑道：“自己给自己送礼？也没有这样吃饱了撑着的事吧！”\n");
        i = ob->value();
        if( !query_temp("songli", me))//防止玩家反复送礼骚扰频道
        {
                CHANNEL_D->do_channel(this_object(), "chat",
                        sprintf("%s恭贺%s和%s新婚大喜，送上贺礼"+MONEY_D->price_str(i)+"！\n",me->name(),query("name1"),query("name2")));
                set_temp("songli", 1, me);
        }
        if( query_temp("songli", me)>10 && i<100000 )
        {
                addn_temp("songli", -1, me);
                call_out("kick",0,me);
        }
        else if( query_temp("songli", me)>7 && i<100000 )
        {
                write("喜来福不悦道：“我警告你啊！你这送礼就到此为止吧，再下去我不客气了！”\n");
                addn_temp("songli", 1, me);
        }
        else if( query_temp("songli", me)>4 && i<100000 )
        {
                write("喜来福收起笑脸道：“你是不是来捣乱的？要送礼就一笔头送完算了！”\n");
                addn_temp("songli", 1, me);
        }
    else
        addn_temp("songli", 1, me);
        addn("money",i);//记录送来的礼金数
        return 1;
}

int ask_party()
{
        object me,ob,wife;
        ob=this_object();
        me=this_player();
        if (! objectp(me)) return 1;
        if( query_temp("host_of_party", me) )
                message_vision("$N对$n说：“您的喜宴不是正在开着吗？”\n", ob, me);
        if( !query_temp("married_party", me) )
                message_vision("$N翻了翻帐本，对$n迟疑的问道：“媒婆好象没有在我这里给您订喜筵，会不会搞错了？”\n", ob,me);
        if( query("gender", me) == "女性" )
                message_vision("$N笑着对$n说道：“媒婆是以新郎的名义在这订酒席，还是叫你的丈夫来问吧！”\n", ob,me);
        if( !query("couple/couple_id", me) )
                message_vision("$N对$n说：新娘子都没来，这喜宴怎么开？\n", ob,me);
        if( !objectp(wife=present(query("couple/couple_id", me),environment(me))) )
                return notify_fail("新娘子都没来，这喜宴怎么开？\n");
        if( query_temp("ready_to_party", ob) )
                message_vision("$N对$n不好意思的说：我这正开着一席呢，要不您明儿再来吧！\n",ob,me);
        if( query("short", environment(ob)) != "喜福堂" )
                message_vision("$N对$n为难的说：“对不起，等我回店准备了再说吧！”\n",ob,me);
        if( query_temp("ready_to_ask", me) )
                message_vision("$N对$n不耐烦的说道：“不是都说了吗？你怎么问个没完！”\n",ob,me);
        else
        {
                set_temp("ready_to_ask", 1, me);//新郎问过了的记号
                set_temp("ready_to_party", 1, ob);//老板开始记号
                set_temp("host_of_party", 1, me);//新郎的记号
                delete_temp("married_party", me);
                if (objectp(wife))
                delete_temp("married_party", wife);
                message_vision("喜来福对$N点点头道：“您老尽管吩咐！我马上给您准备！”\n",me);
                call_out("start_party",1,ob,me);
        }
        return 1;
}

void start_party(object ob,object me)
{
        command("chat* "+name()+"一拱手道：“良宵一刻值千金，酒不醉人人自醉，今日迎宾楼荣幸地为"+query("name1")+
                "和"+query("name2")+"\n大开喜宴，恭迎各位前来捧场！\n\n");
        message_vision("喜老板转身又对$N小声问了几句。\n",me);
        write("您要开始，就输入 kaishi，如果想开席，就输入 kaixi，\n"
                "大家吃饱了，喝足了就可以结束了(jieshu)。");
        delete_temp("ready_to_ask", me);
        set_temp("ready_to_party", 1, me);//新郎准备开始记号
}

int do_start()
{
        object me,ob,obj,*list;
        int i;
        me = this_player();
        ob = this_object();

        if( !query_temp("host_of_party", me) )
        {
                if( !query_temp("married_party", me) )
                        return notify_fail(name()+"对你说：“你又不是新人！喊什么喊？”\n");
                return notify_fail(name()+"对你说：“你先ask xi about 喜宴，让我告诉你酒席进行程序！”\n");
        }
        if( !query_temp("ready_to_party", ob) )
                return notify_fail(name()+"对你说：“开始什么呀，现在又没人办婚宴！”\n");
        if( query_temp("party_start_already", me) )
                return notify_fail(name()+"笑呵呵地对你说：“你看这不是已经开始了嘛！”\n");

        message_vision("$N对$n点点头说：“喜老板，喜宴可以开始了！”\n\n"
                "$n立刻大声喊着：“给客人上～～喜～～酒～～”\n\n",me,ob);
        set_temp("party_start_already", 1, me);//新郎已经开始记号
        delete_temp("ready_to_party", me);
        tell_room( environment(ob), HIY"喜老板又手一挥，几个彩衣乐手立刻吹起唢呐、奏起喜乐。\n"NOR);

        list = all_inventory(environment(me));
        i = sizeof(list);
        while (i--)
        {
       if( obj=new("/d/suzhou/npc/obj/xijiu"))
       obj->move(list[i]);
   }
   tell_room(environment(), "\n从内堂走出一排漂亮的黄衫少女，依次走到每个人面前。\n"
                "黄衫少女递给你一杯斟满喜酒的玉盏又走开了去。\n");
   call_out("finish_party", 600, me,ob);//10分钟后自动结束
   return 1;
}

int do_serve()
{
        object ob,me,food;
        ob=this_object();
        me=this_player();

        if( !query_temp("host_of_party", me) )
                return notify_fail(name()+"斜眼瞪了你一眼道：“主人没说话，你嚷什么？！”\n");
        if( !query_temp("party_start_already", me) )
                return notify_fail(name()+"对你笑说：“还没告诉我开始(kaishi)，我怎么好开席？”\n");

        message_vision("$N大声嚷嚷着：上菜，上菜！\n", me);

        tell_room(environment(me), "“来啦！”四五个小伙计从内堂鱼贯而出，一盘盘美味佳肴立刻摆上了桌。\n");
        if(food=new("/d/suzhou/npc/obj/jiuyan"))
        food->move(environment(me));
        return 1;
}

int do_finish()
{
        object ob=this_object();
        object me=this_player();

        if( !query_temp("host_of_party", me) )
                return notify_fail(name()+"不满意地瞪了你一眼：“你吃你的，不关你事不要乱说话！”\n");

        if( !query_temp("party_start_already", me) )
                return notify_fail(name()+"呵呵笑道：“喜筵不是已经结束了吗！”\n");
        message_vision("$N对$n说道：“客人吃得都不错，十分感谢喜老板的安排！”\n", me, ob);
        remove_call_out("finish_party");
        call_out("finish_party", 2, me,ob);
        return 1;
}

void finish_party(object me,object ob)
{
        int i;
        object *list,ob1,ob2;

        message_vision(HIC"\n$N大声说道：“小小薄宴，怠慢诸位，$n的喜宴就此结束，多谢大家光临！\n"NOR, ob,me);

        if( !me || environment(me) != environment(ob) )
        {
            tell_room(environment(ob), "\n一旁的黄衫少女连忙上来把酒席上的残羹剩菜收拾干净抬下去。\n");
            if(ob1=present("jiuxi", environment(ob))&&!userp(ob1))
            destruct (ob1);
            remove_call_out("give_money");
            call_out("give_money",1,0,ob);
        }

        command("gongxi "+query("id", me));

        set_temp("party_finish", 1, me);
        delete_temp("party_start_already", me);
        delete_temp("host_of_party", me);
        set_temp("party_finish", 1, ob);
        message("vision","\n一旁的黄衫少女连忙上来把酒席上的残羹剩菜收拾干净抬下去。\n",environment(me));
        if(ob1=present("jiuxi", environment(ob))&&!userp(ob1))
            destruct (ob1);
        list = all_inventory(environment(ob));
        i = sizeof(list);
        while (i--)
        {
            ob2=new("/d/suzhou/npc/obj/xitang");
            set("name", me->name()+"和"+query("couple/couple_name", me)+"的喜糖", ob2);
            ob2->move(list[i]);
        }
        tell_room(environment(ob), "\n喜老板吩咐手下的伙计把喜糖一包包地发给每一个人。\n");
        remove_call_out("give_money");
        call_out("give_money",1,me,ob);
}

int give_money(object me,object ob)
{
        int money,v;
        
        delete("no_fight", environment());
        if( !me || environment(me) != environment(ob) )
        {
                   message_vision("喜老板突然向四周一看：“咦？人去哪里了，连代收的礼金都不要了？”一边\n"
                        "摇着头一边向内堂走去，伙计、黄衫少女也一齐走进去，喜福堂一下子空下来了。\n",ob);
                log_file("static/marry_money",sprintf("%s(%s)%s",me->name(),query("id", me),query("money", ob)));
                delete_temp("ready_to_party", ob);
                ob->move("/u/lonely/workroom");//不要直接dest，以备查
           return  1;
        }
        //注：由于实际过程有的玩家会收到大量的喜金，有时会超过负重，造成喜金丢失
        //因此改成进帐户
        message_vision("\n喜老板笑呵呵地走到$N面前，一挥手，旁边的小伙计捧过来一本帐本，喜老板说道：\n"
                "“这是小可代二位收下的客人送上的礼金，一共是"+MONEY_D->price_str(query("money", ob))+"\n"
                "我已经托伙计转进了您的钱庄帐户，您可去查看查看！”说完然后一齐走进内堂不见了。\n",me);
        money=query("money", ob);
        addn("balance", money, me);
        delete_temp("ready_to_party", ob);
          ob->move("/u/lonely/workroom");//不要直接dest，以备查
        return 1;
}

int do_kill(string arg)
{
        write("喜来福冲着你直摇头：“这大喜的日子动手干什么啊！”\n");
        return 1;
}

int do_exert()
{
   write("你鬼鬼祟祟地一运气。\n喜来福冲你瞪了一眼：“刚吃过饭，不要乱用内功！”\n");
   return 1;
}

int do_steal(string arg)
{
        object me = this_player();
        object ob = this_object();
        if( query_temp("steal_xiyan", me)<5 )
        {
                message_vision("$N伸出手，想要偷点什么。\n$n对$N骂道：怎可随便光天化日施盗行窃！\n",me,ob);
                addn_temp("steal_xiyan", 1, me);
                return 1;
        }
        else if( query_temp("steal_xiyan", me)<8 )
        {
                message_vision("喜来福气得对$N骂道：“你要还是贼性不改的话，我叫衙门里的人抓你做牢去！”\n",me);
                addn_temp("steal_xiyan", 1, me);
                return 1;
        }
        message_vision("门外冲进来几个捕快，指着$N问喜来福：“是这个小偷吗？”喜老板道：“正是正是！”\n"
        "于是捕快们一拥而上，将$N拷起，拖了出去。\n",me);
        tell_object(me,"你还没搞清楚是什么事，就被一群捕快拖着出了迎宾楼......\n");
        set("jianyu/what", "steal", me);//做牢原因
        set("jianyu/where", "suzhou", me);//被捕地点
        me->apply_condition("jianyu",20);//做牢时间
        me->move("/d/changan/prison");//进监狱
        return 1;
}

int kick(object me)
{
        if( !me || environment(me) != environment() ) return 0;
        message_vision("喜老板怒喝一声：“警告了你还不听，看脚！”说完，喜来福一抬腿，$N大惊失色，\n"
                "却怎么也无法躲得过这一脚。“嗵！”地一声，身子从窗户里飞了出去。\n"
                "喜老福掸掸身上尘土，呵呵笑道：“没事了，大家坐！坐！！”\n",me);
        tell_room("/d/suzhou/xiaozheng","突然一个人影从西边的迎宾楼二楼飞出来，“蓬”地重重摔在地上，细看却是一个差点摔死的人。\n");
        set_temp("kick", 1, me);
        me->move("/d/suzhou/baodaiqiao");//移到楼下的大街房间里即可
        tell_object(me,"你只觉屁股一吃痛，身子已飞起来，“蓬”地落在地上，你的五脏六腑似乎全震荡起来了……\n");
        if( query("qi", me)>30)addn("qi", -30, me);
        else me->unconcious();
}
