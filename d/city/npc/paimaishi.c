// 拍卖师

inherit NPC;
#include <ansi.h>;
int begin_paimai(string name,int value ,int paimai_count,int m);
int go_paimai(string id,string name,int value,int num,int m);
int report_paimai(object buyer,int money,int num);
int finish_paimai(int num,int sign);
int pay_back(string id, int amount);
int delete_ob(int num);
string to_ch(int money);
void create()
{
        set_name("拍卖师", ({ "paimai shi", "ji", "shi" }) );
                set("nickname", HIY+BLINK "天下第一锤" NOR);
        set("gender", "男性");
        set("age", 45);
        set("no_get", 1);
        set("long",
                "这是一位瘦高的中年人，因为公正无私而被推为天下第一拍卖师。\n");
        set("combat_exp",600000);
        set("shen", 0);
            set("attitude", "friendly");

        set("apply/attack", 100);
        set("apply/defense", 100);

        set("max_qi", 800);
        set("qi", 800);
        set("max_jing", 800);
        set("jing", 800);
        set("max_jingli", 800);
        set("jingli",800);
        set("max_neili", 8000);
        set("neili",8000);
        
        set_skill("force", 300);
        set_skill("unarmed", 300);
        set_skill("sword",300);
        set_skill("parry",300);
        set_skill("dodge", 300);

            setup();

        carry_object("/clone/cloth/cloth")->wear();
}


void init()
{
        ::init();
        add_action("do_paimai", "paimai");
        add_action("do_paimailist", "paimailist");
        add_action("do_yao", "yao");
        
}
int do_paimai(string arg)
{
        object who,ob;
        int money,clone_number,paimai_count,i,value,sale_price;
        string id,file_name;
        mapping fpaimai,vpaimai,ipaimai,npaimai,lpaimai,opaimai,spaimai;
        string* terms;
        
        fpaimai = query("fpaimai");
        vpaimai = query("vpaimai");
        ipaimai = query("ipaimai");
        npaimai = query("npaimai");
        lpaimai = query("lpaimai");
        opaimai = query("opaimai");
        spaimai = query("opaimai");
        
        who=this_player();
        
        if( who->is_busy() )
         return notify_fail("你的动作还没有完成，不能提交物品进行拍卖。\n");
        if( who->query_condition("auction_forbindden"))
                return notify_fail("你目前不能参与拍卖。\n");
    if( !arg || sscanf(arg, "%s with %d",id, money)!=2 )
                return notify_fail("指令格式：paimai <物品id> with <底价(silver为单位)> \n");
        if( !ob=present(id, who))
                return notify_fail("你身上没有这样东西。\n");
        if( query("money_id", ob) )
                return notify_fail("你要拍卖「钱」？\n");
        if( query("value", ob)<10 || money == 0 )
                return notify_fail("拍卖师说道：这件东西不值钱，你就别卖了！\n");
        if( query("no_sell", ob) && !query("can_auction", ob) )
                return notify_fail("拍卖师说道：这样东西不能拍卖了！\n");
        if( query("no_drop", ob) && !query("can_auction", ob) )
                return notify_fail("拍卖师说道：扔不掉的东西想来卖，你当我这里是垃圾堆啊！\n");
        if( ob->query_unique() && !query("can_auction", ob) )
                return notify_fail("拍卖师说道的说：这是孤品啊，我们这里可不敢承接这个买卖了！\n");
    if( money<(100+query("value", ob)/100) )
                return notify_fail("拍卖师说道：您想做赔本生意，嘿嘿，您财大气粗无所谓，小店的声誉可是要受损的。\n");
    if(money<0||money>1000000)
                return notify_fail("拍卖师说道：你出的价格是非法的。\n"); //防止溢出
        if( query("balance", who)<10000 )
                return notify_fail("拍卖师说道：你账号里的钱不够支付手续费！\n");
   
        addn("balance", -10000, who);
        command("sys"+query("name", who)+"("+query("id", who)+")"+NOR+query("name", ob)+HIC+"进行拍卖。\n"NOR);
        command("chat"+"有人提交"+NOR+query("name", ob)+HIC+"进行拍卖，请使用"+HIW"〖"HIG"拍卖"HIW"〗"NOR+HIC"频道"HIY"（ＢＩＬＬ）"HIC"了解具体情况。"NOR);
    who->apply_condition("auction_forbindden",1+random(10));
        sscanf(file_name(ob),"%s#%d",file_name,clone_number);

        if( mapp(fpaimai) &&  sizeof(fpaimai) )
                addn("total_number",1);
        else
                set("total_number",0);
        
        value=query("value", ob);
        sale_price=query_temp("sale_price", ob);
        if (sale_price>0)
                sale_price= sale_price>value?value:sale_price;

        set("fpaimai/"+ sprintf("%d",query("total_number")),file_name);
        set("vpaimai/"+sprintf("%d",query("total_number")), money);
        set("ipaimai/"+sprintf("%d",query("total_number")),query("id", who));
        set("npaimai/"+sprintf("%d",query("total_number")),query("name", ob));
        set("lpaimai/"+sprintf("%d",query("total_number")), 1);
        set("opaimai/"+sprintf("%d",query("total_number")),query("id", who));
        set("spaimai/"+sprintf("%d",query("total_number")), sale_price);
        
        if (query("total_number")==0 || query("lpaimai/"+sprintf("%d",query("number")))==0)
        {
                set("value",money);
                set("pnum",0);
                set("number",query("total_number")>0?query("number")+1:0);
                call_out("begin_paimai",5,query("name", ob),money,query("number"),0);
        }
        
        if(!ob->query_unique())
                destruct(ob); 
        else
        {
                ob->move(this_object());
                call_out("destobj",700,ob);
        }
        return 1;
}
void destobj(object ob)
{
        if(!ob)
                return;
    destruct(ob); 
}
int begin_paimai(string name,int money,int num,int m)
{
        string mon;
        m+=1;
        if (m==1)
        {
                command("bill "+"现在开始拍卖 "NOR+name+HIG+" 的所有权。"+NOR);
        }
        set("on_paimai",1);
        mon = to_ch(money);
        command("bill "+NOR+name+HIG+"底价"+mon+"第"+chinese_number(m)+"次");
        command("bill "+name+HIG"是本店第『"+chinese_number(num)+"』号拍卖品，有意者请使用ＢＩＤ命令进行竞买。"NOR);

        if (!(m==3))
                call_out("begin_paimai",20,name,money,num,m);
        else
                call_out("finish_paimai",2,num,0);      
}
int finish_paimai(int num,int sign)
{
        string id,owner_id;
        object buyer,owner;
        int i;

        
        id=query("ipaimai/" + sprintf("%d", num));
        owner_id=query("opaimai/" + sprintf("%d", num));
        set("lpaimai/"+sprintf("%d",num), 0);
                
        buyer=find_player(id);
        owner=find_player(owner_id);
        if (sign==0)
        {
                command("bill "+query("npaimai/" + sprintf("%d", num))+HIG+" 的所有权拍卖流标了。"+NOR);
                if(owner)
                        tell_object(owner,HIR"你的东西没有卖出去，请在十分钟内来拍卖屋来取回自己的物品。\n"NOR);
        }
        else            
        {
        if( !query_temp("invisibility_buyer", buyer) )
        {
                command("bill成交!"+query("id", buyer)+"获得了"+NOR+query("npaimai/"+sprintf("%d",num))+HIG+"的所有权。"+NOR);
        }
        else
        {
                command("bill 成交! 有人获得了 "+NOR+query("npaimai/" + sprintf("%d", num))+HIW+" 的所有权。"+NOR);
                command("sys成交!"+query("id", buyer)+"获得了"+NOR+query("npaimai/"+sprintf("%d",num))+HIG+"的所有权。"+NOR);
        }
                if (buyer)
                        tell_object(buyer,HIR"你获得了 "+NOR+query("npaimai/" + sprintf("%d", num))+HIR+" 的所有权，请在十分钟内来拍卖屋取回你买的东西。\n"NOR);
                if (owner)
                        tell_object(owner,HIR"你的"+NOR+query("npaimai/" + sprintf("%d", num))+HIR+"卖了"
                        +chinese_number(query("vpaimai/" + sprintf("%d", num)))+"两银子，扣除5%手续费，其余的已经加入你的户头了。\n"NOR);        
        }
    if(buyer)
          buyer->apply_condition("auction_forbindden",1+random(10));
        set("on_paimai",0);
        
        if (query("pnum"))
            pay_back(owner_id,query("vpaimai/" + sprintf("%d", num))*95);
        
        call_out("delete_ob",600,num);

        num=num+1;
        if (query("lpaimai/" + sprintf("%d", num))==1)
        {
                set("value",query("vpaimai/" + sprintf("%d", num)));
                set("number",num);
                set("pnum",0);
                call_out("begin_paimai",5,query("npaimai/" + sprintf("%d", num)),query("vpaimai/" + sprintf("%d", num)),num,0);
        }
        return 1;
}
int report_paimai(object buyer,int money,int num)
{
        string mon;
        remove_call_out("begin_paimai");
        remove_call_out("finish_paimai");
        remove_call_out("go_paimai");
        
        if(query("pnum")) // pnum是判断是否有人投标的标志　 
        {
                pay_back(query("ipaimai/" + sprintf("%d", num)),query("vpaimai/" + sprintf("%d", num))*100);//归还前一个竞买者的钱　
                addn("pnum",1);
        }
        addn("balance", (0-money*100), buyer);
        set("vpaimai/"+sprintf("%d",num), money);
        set("ipaimai/"+sprintf("%d",num),query("id", buyer));
        set("value",money);
        mon =to_ch(money);
        if( !query_temp("invisibility_buyer", buyer) )
        {
           if (!query("pnum"))
                   addn("pnum",1);
                command("bill"+query("id", buyer)+"出价"+mon+"购入"+NOR+query("npaimai/"+sprintf("%d",num))+HIG"的所有权。");
        call_out("go_paimai",5,query("name", buyer)+"("+query("id", buyer)+")",query("npaimai/"+sprintf("%d",num)),money,num,0);
        }
        else
        {
           if (!query("pnum"))
           addn("pnum",1);
       command("sys"+query("id", buyer)+"出价"+mon+"购入"+NOR+query("npaimai/"+sprintf("%d",num))+HIG"的所有权。");
       command("bill  有人出价 "+chinese_number(money)+"两银子 购入"+NOR+query("npaimai/" + sprintf("%d", num))+HIG"的所有权。");
       call_out("go_paimai",5,"某人",query("npaimai/" + sprintf("%d", num)),money,num,0);
        }
        return 1;
}
int pay_back(string id, int amount)
{
    object who;
    
    who=find_player(id);
    if(who)
        {
                addn("balance", amount, who);
                if(!who->save(1)) 
                {
                        log_file("paimai_log","Failed to return "+amount+
                                " coin to "+id+"\n");
                        return 0;
                }
        log_file("paimai_log","pay "+amount+" to "+id+"\n");
        return 1;
    } 
        else
        {
                who=new(USER_OB);
                set("id", id, who);
                if(!who->restore())
                {
                        log_file("paimai_log","Failed to return "+amount+
                                " coin to "+id+"\n");
                        destruct(who);
                        return 0;
                }
                else 
                {
                        addn("balance", amount, who);
                        if(!who->save(1))
                        { // save(1) will not erase autoload.
                                log_file("paimai_log","Failed to return "+amount+
                                        " coin to "+id+"\n");
                                destruct(who);
                                return 0;
                        } 
                        log_file("paimai_log","pay "+amount+" to "+id+"\n");
                        destruct(who);
                        return 1;
                }
    }
}
int go_paimai(string id,string name,int money,int num,int m)
{
        string mon;
        m+=1;
        mon = to_ch(money);
        command("bill "+id+" 出价 "+mon+"购入 "+NOR+name+HIG+" 的所有权，第"+chinese_number(m)+"次");
        command("bill "+name+HIG"是本店第『"+chinese_number(num)+"』号拍卖品，有意者请使用ＢＩＤ命令进行竞买。"NOR);
        if (!(m==3))
                call_out("go_paimai",20,id,name,money,num,m);
        else
                call_out("finish_paimai",5,num,1);      
}
int do_paimailist()
{
        int i;
        
        for(i=query("number")+1;;i++)
        {
                if (query("lpaimai/" + sprintf("%d", i))==1)
                {
                        printf("%-10s： 底价 %-3d 两银子 \n",query("npaimai/" + sprintf("%d", i)),query("vpaimai/" + sprintf("%d", i)));
                }
                else
                        return 1;
        }
        return 1;
}
int do_yao()
{
        mapping fpaimai,vpaimai,ipaimai,npaimai,lpaimai,spaimai;
        string* terms;
        string id;
        object ob;
        int i;

        fpaimai = query("fpaimai");
        vpaimai = query("vpaimai");
        ipaimai = query("ipaimai");
        npaimai = query("npaimai");
        lpaimai = query("lpaimai");
        spaimai = query("spaimai");
        
        if( mapp(fpaimai) &&  sizeof(fpaimai) )
        {
                terms=keys(fpaimai);
        
                for(i=0;i<sizeof(terms);i++)
                {
                        if( ipaimai[terms[i]] == query("id", this_player()) && lpaimai[terms[i]] == 0 )
                        {
                                ob=new(fpaimai[terms[i]]);
                                if (spaimai[terms[i]]>0)
                                        set_temp("sale_price", spaimai[terms[i]], ob);
                                ob->move(this_player());
                                if( ob->query_unique() || query("can_auction", ob) )
                                        set("can_auction", 0, ob);
                                ipaimai[terms[i]]="paimai shi";
                                message_vision(CYN+"拍卖师将"+NOR+npaimai[terms[i]]+CYN+"交给$N。\n"NOR, this_player(),this_object());
                                return 1;
                        }
                }
        }
        tell_object(this_player(),"这里没有属于你的物品。\n");
        return 1;
}
int delete_ob(int num)
{
        delete("npaimai/"+sprintf("%d",num));
        delete("ipaimai/"+sprintf("%d",num));
        delete("vpaimai/"+sprintf("%d",num));
        delete("lpaimai/"+sprintf("%d",num));
        delete("fpaimai/"+sprintf("%d",num));
        delete("spaimai/"+sprintf("%d",num));
        
        return 1;
}

string to_ch(int money)
{
        int gold,silver;
        string mon;
        gold = money/100;
    if(gold)
                mon =chinese_number(gold)+"两黄金";
        silver = money-gold*100;
        if(silver)
                mon +="又"+chinese_number(silver)+"两白银";
        mon +="("+sprintf("%d",money)+" silver)";
    set_temp("price",mon);
    return mon;
}