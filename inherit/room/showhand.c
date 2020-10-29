// suoha.c 梭哈，只支持两人, Written by LLM
#define DIAN(x)     (x-1)/4
#define HUA(x)     x%4
#include <ansi.h>
inherit ROOM;

object *player=({});//玩家
int *cards = ({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
20,21,22,23,24,25,26,27,28});//所有的牌
int yazhu=0;//可以押注的标记
int chouma=0;//桌面已经押上的筹码
int yazhu_chouma=0;//别人押的让你跟的筹码数
int wait_time=0;//等待最后读秒记号
int quansuo=0;//全梭
mapping *suoha_cards=({
([
"anpai":0,
"mingpai":({}),
]),//庄家的牌
([
"anpai":0,
"mingpai":({}),
]),//对家的牌
});
string *all_card=({"８","９","⒑","Ｊ","Ｑ","Ｋ","Ａ" });
string *all_sort=({HIB"黑桃",HIR"方片",HIC"草花",HIR"红桃",});
string *all_pai=({"散牌","一对","两对","三条","顺子","同花","飞机","炸弹","同花顺"});

void suoha_init();
void deal_an_card();
void deal_ming_card();
int check_player(object);
int do_yazhu(string);
int do_gen();
object gen_ob(object);
void ob_win(object);
void game_over();
int do_buya();
int do_leave();
int do_quansuo();
string look_pai();
string type_paiju(object);
int check_chouma();
string query_obs();

string type_card(int x)//单张表述
{
    return sprintf("%s%s%s"NOR,all_sort[HUA(x)],HIW,all_card[DIAN(x)]);
}

string type_cards(mapping pai)//多张表述
{
    switch(pai["lv"])
    {
    case 2:
       return sprintf("%s大对加%s小对，两对子",type_card(pai["ddui"]),type_card(pai["xdui"]));
    case 3:
    case 6:
    case 7:
        return sprintf(HIW"%s%s%s",all_card[DIAN(pai["max"])],NOR,all_pai[pai["lv"]]);
    default:
    return sprintf("%s%s",type_card(pai["max"]),all_pai[pai["lv"]]);
    }
}

mapping juesuan(int *ob_allcard)//决算出牌的类型
{
    mapping pai;
    int i,x,flag,*L;

    flag=0;
    x=sizeof(ob_allcard);
    L=sort_array(ob_allcard,1);//排序
    switch(x)
    {
    case 1:
        pai=([
            "lv": 0,
            "max" : L[0],
            ]);
        break;
    case 2:
        if(DIAN(L[0])==DIAN(L[1]))//点数相同是对子
            pai=([
                "lv": 1,
                "max" : L[1],//取对子的大牌
            ]);
        else
            pai=([
                "lv": 0,
                "max" : L[1],
            ]);
        break;
    case 3:
        if(DIAN(L[0])==DIAN(L[2]))//第一与第三点数相同是三只
            pai=([
                "lv": 3,
                "max" : L[2],//随便取一牌
            ]);
        else if(DIAN(L[0])==DIAN(L[1]))//只有一二点数相同 对子
            pai=([
                "lv": 1,
                "max" : L[1],//取大牌
            ]);
        else if(DIAN(L[1])==DIAN(L[2]))//只有二三点数相同 对子
            pai=([
                "lv": 1,
                "max" : L[2],//取大牌
            ]);
        else
            pai=([
                "lv": 0,
                "max" : L[2],//取最大牌
            ]);
        break;
    case 4:
        if(DIAN(L[0])+1==DIAN(L[1])&&DIAN(L[1])+1==DIAN(L[2])&&DIAN(L[2])+1==DIAN(L[3]))
            flag=1;
        if(HUA(L[0])==HUA(L[1])&&HUA(L[2])==HUA(L[3])&&HUA(L[1])==HUA(L[2]))//同花，再看是否顺子
        {
            if(!flag)//同花
                pai=([
                "lv": 5,
                "max" : L[3],
                ]);
            else//同花顺
                pai=([
                "lv": 8,
                "max" : L[3],
                ]);
        }
        else if(flag)//顺子
            pai=([
            "lv": 4,
            "max" : L[3],
            ]);
        else if(DIAN(L[0])==DIAN(L[3]))//一四点数相同是炸弹
            pai=([
                "lv": 7,
                "max" : L[0],//随便取一牌
            ]);
        else if(DIAN(L[0])==DIAN(L[2])||DIAN(L[1])==DIAN(L[3]))//一三或二四点数相同是三条
            pai=([
                "lv": 3,
                "max" : L[2],//随便取一中间牌
            ]);
        else if(DIAN(L[0])==DIAN(L[1])&&DIAN(L[2])==DIAN(L[3]))//一二且三四点数相同是两对
            pai=([
                "lv": 2,
                "xdui":L[1],
                "ddui":L[3],
                "max":L[3],//取最大的牌
            ]);
        else
        {
            if(DIAN(L[0])==DIAN(L[1])) flag=1;
            else if(DIAN(L[1])==DIAN(L[2])) flag=2;
            else if(DIAN(L[2])==DIAN(L[3])) flag=3;
        if(flag)
            pai=([
                "lv": 1,
                "max" : L[flag],//取对子的大牌
            ]);
        else
            pai=([
                "lv": 0,
                "max" : L[3],//取最大的牌
            ]);
        }
        break;
    case 5:
        if(DIAN(L[0])+1==DIAN(L[1])&&DIAN(L[1])+1==DIAN(L[2])&&DIAN(L[2])+1==DIAN(L[3])&&DIAN(L[3])+1==DIAN(L[4]))
            flag=1;
        if(HUA(L[0])==HUA(L[1])&&HUA(L[1])==HUA(L[2])&&HUA(L[2])==HUA(L[3])
            &&HUA(L[3])==HUA(L[4]))//是同花，只有是否顺子两个可能
        {
            if(!flag)//同花
                pai=([
                "lv": 5,
                "max" : L[4],
                ]);
            else//同花顺
                pai=([
                "lv": 8,
                "max" : L[4],
                ]);
        }
        else if(flag)//顺子
            pai=([
            "lv": 4,
            "max" : L[4],
            ]);
        else if(DIAN(L[0])==DIAN(L[3])||DIAN(L[1])==DIAN(L[4]))//1,4或2,5相同，则为炸弹，取第四张
        {
            pai=([
            "lv": 7,
            "max" : L[4],//花色无关紧要，炸弹只要判断点数
            ]);
        }
        else if(DIAN(L[0])==DIAN(L[2])||DIAN(L[2])==DIAN(L[4])||DIAN(L[1])==DIAN(L[3]))//三张一样
        {
            if((DIAN(L[0])==DIAN(L[2])&&DIAN(L[3])==DIAN(L[4]))
                ||(DIAN(L[2])==DIAN(L[4])&&DIAN(L[0])==DIAN(L[1])) )//所剩两张是对子
            {
                pai=([
                "lv": 6,
                "max" : L[2],//取中间那张，花色无关紧要
                ]);
            }
            else
                pai=([
                "lv":3,
                "max" : L[2],//取中间那张，花色无关紧要
                ]);
        }
        else
        {
        flag=0;
        if(DIAN(L[0])==DIAN(L[1])&&DIAN(L[2])==DIAN(L[3])) flag=3;
        if(DIAN(L[0])==DIAN(L[1])&&DIAN(L[3])==DIAN(L[4])) flag=4;
        if(DIAN(L[1])==DIAN(L[2])&&DIAN(L[3])==DIAN(L[4])) flag=4;
        if(flag)//小对子肯定有1，大对子肯定有3
        {
            pai=([
                "lv": 2,
                "xdui":L[1],
                "ddui":L[3],
                "max" : L[flag],//取大对子的大牌
            ]);
        }
        else
        {
        for(i=0;i<4;i++)
            if(DIAN(L[i])==DIAN(L[i+1])) flag=(i+1);
        if(flag)
            pai=([
            "lv": 1,
            "max" : L[flag],//取对子的大牌
            ]);
        else
            pai=([
            "lv": 0,
            "max" : L[4],//取最大的牌
            ]);
        }
        }
        break;
    }
    return pai;
}

int bi_daxiao(mapping card1,mapping card2)//比大小,card1大就是0，card2大就是1
{
    if(card1["lv"]==card2["lv"])//同类相比
    {
        if(card1["lv"]== 2)//两对子
        {
            if(DIAN(card1["ddui"])>DIAN(card2["ddui"]))
                return 0;
            else if(DIAN(card1["ddui"])==DIAN(card2["ddui"]))
            {
                if(DIAN(card1["xdui"])>DIAN(card2["xdui"])
                    ||(DIAN(card1["xdui"])==DIAN(card2["xdui"])
                    &&card1["max"]>card2["max"]))
                    return 0;
                else return 1;
            }
            else return 1;
        }
        else if(card1["max"]>card2["max"]) return 0;
        else return 1;
    }
    else if(card1["lv"]>card2["lv"]) return 0;
    else return 1;
}

int do_sit()
{
        object me;
        int i;
        me = this_player();

    if( query_temp("suoha/being", me) )
                return notify_fail("你已经坐上桌了！\n");
    if( query_temp("duchang_chouma", me)<200 )
        return notify_fail("你的筹码太少了！\n");
    i=sizeof(player);
        if (i<2)//还有空位
        {
        set_temp("suoha/being", 1, me);
                player+=({me});
                addn_temp("duchang_chouma", -5, me);//押５个
                yazhu_chouma+=5;//筹码
        i=sizeof(player);
        message_vision("$N拿出5个筹码押出去，坐上了座位！\n",me);
        if (i == 2)//满2人自动开始
                {
               tell_room(this_object(), HIM"    好，可以开始发牌了！\n"NOR);
                        suoha_init();
                }
                return 1;
        }
        else
                return notify_fail("这里已经满人了！\n");
}

void suoha_init()
{
    chouma+=yazhu_chouma;
    yazhu_chouma=0;//清零
    deal_an_card();
}

void deal_an_card()//发暗牌
{
        int i, j;

    i=random(sizeof(cards));//随机取一张
    suoha_cards[0]["anpai"]=cards[i];//发到手中暗牌
    message_vision("\n$N拿到了一张暗牌，看了一眼后，迅速地盖在桌上！\n",player[0]);
    tell_object(player[0],"这张暗牌是："+type_card(cards[i])+"！\n");
    cards-=({cards[i]});//桌上这张牌被发掉

    i=random(sizeof(cards));//从剩下来的牌中随机再取一张
    suoha_cards[1]["anpai"]=cards[i];//发到手中暗牌
    message_vision("\n$N拿到了一张暗牌，看了一眼后，迅速地盖在桌上！\n",player[1]);
    tell_object(player[1],"这张暗牌是："+type_card(cards[i])+"！\n");
    cards-=({cards[i]});//桌上这张牌被发掉
    tell_room(this_object(), HIM"    现在开始给每个人发明牌了！\n"NOR);
        remove_call_out("deal_ming_card");//一秒后发第二张
        call_out("deal_ming_card",1);//一秒后发第二张
}

void deal_ming_card()//发明牌
{
    int i,j;
    string arg;
    mapping card1,card2;

    i=random(sizeof(cards));//随机取一张
    suoha_cards[0]["mingpai"]+=({cards[i]});//发到手中的明牌
    message_vision("\n$N拿到了一张：" +type_card(cards[i])+"！\n",player[0]);
    cards-=({cards[i]});//桌上这张牌被发掉
    i=random(sizeof(cards));//剩下的牌中随机取一张
    suoha_cards[1]["mingpai"]+=({cards[i]});//发到手中第一张明牌
    message_vision("\n$N拿到了一张：" +type_card(cards[i])+"！\n",player[1]);
    cards-=({cards[i]});//桌上这张牌被发掉

    card1=juesuan(suoha_cards[0]["mingpai"]);//决算出牌型
    card2=juesuan(suoha_cards[1]["mingpai"]);//决算出牌型
    j=bi_daxiao(card1,card2);//比出大牌
    tell_object(player[0],type_paiju(player[0]));
    tell_object(player[1],type_paiju(player[1]));
    if(j) arg=type_cards(card2);
    else arg=type_cards(card1);
    message_vision(HIY"\n　　$N的"+arg+HIY"说话！\n"NOR,player[j]);
    set_temp("suoha/shuohua", 1, player[j]);
    tell_object(player[j],"\n　想押就ya <筹码数>,不押(buya)就认输！\n");
        yazhu=1;//可以押注了
        call_out("check_player",60,player[j]);//一分钟后检查
    return;
}

int check_player(object me)
{
    object ob;

    if(!wait_time)
    {
        wait_time=1;
        call_out("check_player",10,me);//最后十秒;
        tell_object(me,"你还有十秒钟时间，超时就表示认输！\n");
        return 1;
    }
    yazhu=0;
    wait_time=0;
    message_vision("$N超时放弃了，大家亮底牌！\n");
    ob=gen_ob(me);
    call_out("juesheng",0,ob,1);//决胜
    return 1;
}

int do_yazhu(string arg)
{
    int i;
    string str;
    object me,ob;
    me=this_player();
    if(!yazhu) return notify_fail("现在不是下注的时候！\n");
    if( !query_temp("suoha/shuohua", me))//是否为说话的方向
        return notify_fail("现在不是你说话！\n");
     if(!arg||sscanf(arg,"%d",i)!=1||(i!=5&&i!=10&&i!=20))
        return notify_fail("你要押多少筹码？可选5个,10个,20个筹码。\n");
    remove_call_out("check_player");//清除延时呼叫
    addn_temp("duchang_chouma", -i, me);
    yazhu_chouma=i;
    message_vision("$N哼了一声，推上去一些筹码说：“我押 "+i+" 个！敢跟吗？”\n",me);
    ob=gen_ob(me);
    tell_object(ob,"你要跟(gen)的话，就是再上"+i+"个筹码，不押(buya)就是认输！\n");
    delete_temp("suoha/shuohua", me);
    set_temp("suoha/genhua", 1, ob);
    call_out("check_player",60,ob);
    return 1;
}

int do_gen()
{
    int i;
    object me,ob;
    me=this_player();
    if(!yazhu) return notify_fail("现在不是跟注的时候！\n");
    if( !query_temp("suoha/genhua", me) )
        return notify_fail("现在不是你说话！\n");
    remove_call_out("check_player");//清除延时呼叫
    i=yazhu_chouma;//前面人押下的筹码数
    addn_temp("duchang_chouma", -i, me);
    chouma+=(i*2);//两个人的筹码都加进去
    yazhu_chouma=0;//清零
    message_vision("$N微微一笑，也推了一些筹码上去，说：“我跟 ！”\n",me);
    delete_temp("suoha/genhua", me);
    if(sizeof(suoha_cards[0]["mingpai"])==4)//牌发完了
    {
        yazhu=0;
        message_vision("\n牌已发完，大家亮底牌！\n",me);
        call_out("juesheng",1,me,0);//决胜
    }
    else//否则再发牌
    {
        remove_call_out("deal_ming_card");
            call_out("deal_ming_card",1);
        }
    return 1;
}
//跟牌的人
object gen_ob(object ob)
{
   if(sizeof(player)<2) return 0;
    if(player[0]==ob)
        return player[1];
    else
        return player[0];
}

int juesheng(object ob,int flag)//flag为真,则不管结果都是ob胜
{
    mapping card1,card2;
    int i,*pai1,*pai2;

    pai1=suoha_cards[0]["mingpai"];
    pai1+=({suoha_cards[0]["anpai"]});
    card1=juesuan(pai1);

    pai2=suoha_cards[1]["mingpai"];
    pai2+=({suoha_cards[1]["anpai"]});
    card2=juesuan(pai2);

    i=bi_daxiao(card1,card2);

    message_vision("\n$N的牌是『"+type_cards(card1)+"』\n"
    "\n$n的牌是『"+type_cards(card2)+"』\n",player[0],player[1]);
    if(!flag)
        ob=player[i];
    else
    {
        if(ob!=player[i])
            message_vision("$N懊悔地拍拍后脑勺：“早知道我就......！”\n",player[i]);
        else
            message_vision("$N得意地点点头道：也亏你有自知之明啊！\n",player[i]);
    }
    message_vision("\n恭喜$N胜出，桌上筹码全收！\n",ob);
    ob_win(ob);
    return 1;
}

void ob_win(object ob)
{
    addn_temp("duchang_chouma", chouma, ob);
    message_vision("\n这一局，$N一共赢了"+chouma+"个筹码！\n",ob);
    game_over();
}

void game_over()
{
    if(sizeof(player))
    {
        delete_temp("suoha", player[0]);
        message_vision("$N站了起来。\n",player[0]);
    }
    if(sizeof(player)>1)
    {
        delete_temp("suoha", player[1]);
        message_vision("$N站了起来。\n",player[1]);
    }
    player=({});
    chouma=0;
    yazhu_chouma=0;
    suoha_cards=({
    ([
        "anpai":0,
        "mingpai":({}),
    ]),//庄家的牌
    ([
        "anpai":0,
        "mingpai":({}),
    ]),//对家的牌
    });
    wait_time=0;
    quansuo=0;
    cards =({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28});//所有的牌
//--------end---------
}

int do_buya()
{
    int i;
    object me,ob;
    me=this_player();
    if(!yazhu) return notify_fail("现在不是跟注的时候！\n");
    if( !query_temp("suoha/shuohua", me) && !query_temp("suoha/genhua", me))//是否为说话的方向
        return notify_fail("现在不是你说话！\n");
    remove_call_out("check_player");//清除延时呼叫

    chouma+=yazhu_chouma;//加进前面人押下的筹码数
    yazhu_chouma=0;//清零
    message_vision("$N皱了皱眉，突然一笑，说：“我不跟了 ！”\n",me);
    yazhu=0;
    message_vision("$N放弃跟牌，大家亮底牌！\n",me);
    ob=gen_ob(me);
    call_out("juesheng",1,ob,1);//决胜
    return 1;
}

int do_leave()
{
    object me,ob;
    me = this_player();

    if( !query_temp("suoha/being", me) )
                return notify_fail("你现在没有在玩梭哈！想走就直接出大门。\n");
    ob=gen_ob(me);
    if(ob)//已经有两个人
    {
        if(!yazhu)//还未发明牌
            return notify_fail("你现在不能离开!\n");
        yazhu=0;
        remove_call_out("check_player");//清除延时呼叫
        message_vision("$N不想再玩了！\n",me);
        chouma+=yazhu_chouma;//加进前面人押下的筹码数
        call_out("juesheng",0,ob,1);//决胜
    }
    else//只有一个人，就是还没开局
    {
        addn_temp("duchang_chouma", yazhu_chouma, me);//将刚刚押的返还
        yazhu=0;
        remove_call_out("check_player");//清除延时呼叫
        message_vision("$N不想再玩了！\n",me);
        chouma+=yazhu_chouma;//加进前面人押下的筹码数
        call_out("game_over",0);//结束
    }
    return 1;
}

int do_quansuo()//全梭
{
    int i;
    string str;
    object me,ob;
    me=this_player();
    if(!yazhu) return notify_fail("现在不是下注的时候！\n");
    if(sizeof(suoha_cards[0]["mingpai"])!=4)//牌发完了,最后一轮
        return notify_fail("现在不是最后一张，不能showhand！\n");
    if(quansuo)
        return notify_fail("对方已经showhand了，你只要决定跟(gen)还是不跟(buya)！\n");
    if( !query_temp("suoha/shuohua", me) && !query_temp("suoha/genhua", me) )
        return notify_fail("现在不是你说话！\n");
    remove_call_out("check_player");//清除延时呼叫
    quansuo=1;
    if( query_temp("suoha/shuohua", me))//说话方
    {
    i=(200-chouma/2);//最高是200,台面上有一半
    addn_temp("duchang_chouma", -i, me);
        delete_temp("suoha/shuohua", me);
    yazhu_chouma=i;
    }
    else if( query_temp("suoha/genhua", me))//跟话方
    {
    i=yazhu_chouma;//先跟上前面的人押的注
    addn_temp("duchang_chouma", -i, me);
    chouma+=i*2;
    i=(200-chouma/2);
    addn_temp("duchang_chouma", -i, me);
        delete_temp("suoha/genhua", me);
    yazhu_chouma=i;
    }
    message_vision("$N将面前的筹码“呼”地一下全推了上去：“我全梭了！敢跟吗？”\n",me);
    ob=gen_ob(me);
    tell_object(ob,"你要跟(gen)的话，就是再上"+i+"个筹码，不押(buya)就是认输！\n");
    set_temp("suoha/genhua", 1, ob);
    call_out("check_player",60,ob);
    return 1;
}

string look_pai()
{
    switch(sizeof(player))
    {
    case 0:
        return "桌上的牌局还没有开始呢！\n";
    case 1:
        return "现在"+player[0]->name()+"正坐在桌上等候别人的加入！\n";
    case 2:
        return type_paiju(this_player());
    }
}

string type_paiju(object me)
{
    string str,name1,name2,an1,an2;
    int *pai1,*pai2,i,j,k;

    pai1=suoha_cards[0]["mingpai"];
    pai2=suoha_cards[1]["mingpai"];
    i=sizeof(pai1);
    j=sizeof(pai2);
    an1=an2="※※※";//默认
    if(player[0]==me)
    {
        an1= type_card(suoha_cards[0]["anpai"]);
        name1="你";
    }
    else
        name1=player[0]->name();
    if(player[1]==me)
    {
        an2= type_card(suoha_cards[1]["anpai"]);
        name2="你";
    }
    else
        name2=player[1]->name();
    str=sprintf("　　%s的牌：%s%s\n"
"┌───┐┌───┐┌───┐┌───┐┌───┐\n"
"│※※※││　　　││　　　││　　　││　　　│\n"
"│%s│",name1,(query_temp("suoha/shuohua", player[0])?HIW"说话"NOR:""),
    (query_temp("suoha/genhua", player[0])?HIW"跟话"NOR:""),an1);
    for(k=0;k<4;k++)
    {
        if(k<i)
            str+=sprintf("│%s│",type_card(pai1[k]));
        else
            str+="│　　　│";
    }
    str+=sprintf("\n"
"│※※※││　　　││　　　││　　　││　　　│\n"
"└───┘└───┘└───┘└───┘└───┘\n\n"
"　　%s的牌：%s%s\n"
"┌───┐┌───┐┌───┐┌───┐┌───┐\n"
"│※※※││　　　││　　　││　　　││　　　│\n"
"│%s│",name2,(query_temp("suoha/shuohua", player[1])?HIW"说话"NOR:""),
    (query_temp("suoha/genhua", player[1])?HIW"跟话"NOR:""),an2);
    for(k=0;k<4;k++)
    {
        if(k<j)
            str+=sprintf("│%s│",type_card(pai2[k]));
        else
            str+="│　　　│";
    }
    str+="\n"
"│※※※││　　　││　　　││　　　││　　　│\n"
"└───┘└───┘└───┘└───┘└───┘\n\n";
    str+=sprintf("　桌面上的筹码数是%d只，要跟进的筹码数为%d只。\n\n",chouma,yazhu_chouma);
    return str;
}

int valid_leave(object me, string dir)
{
    if( query_temp("suoha", me) )
        return notify_fail("你正在打牌呢！要想走先离开(leave)牌桌！\n");
    return ::valid_leave(me, dir);
}

int check_chouma()
{
    int i;
    object me=this_player();
    if( !i=query_temp("duchang_chouma", me) )
        return notify_fail("你身上没有任何筹码！\n");
    write("目前你身上一共有"+chinese_number(i)+"只筹码！\n");
    return 1;
}