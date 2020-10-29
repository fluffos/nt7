// This program is a part of NITAN MudLIB
// redl 2015.1

#include <ansi.h>
#include <socket.h>
#include <socket_err.h>
#include <time.h>
#include <localtime.h>
#include <mudlib.h>

inherit NPC;
inherit F_NOCLONE;

#define MS sprintf("%c%c", 13, 10 )
#define CC sprintf("%c", 10 )
#define MSG(x)  CHANNEL_D->channel_broadcast("nch", x)
#define NTRATIO 20      //1人民币:泥潭币
#define GIFT1000 0

mapping giftlist = ([   //每1000NT赠品
                                "/d/emei/obj/pantao"                            :       100,
                                "/d/dongtian/obj/wanxiangbook"          :       20,
                                "/kungfu/class/sky/obj/shenjiu"         :       5,
                                "/clone/goods/tianjing"                         :       1,
                                ]);
string *firstgift = ({  //第一次充值就赠
                "/d/emei/obj/pantao",
                "/u/redl/obj/fanghuamu",
                "/u/redl/obj/chutou3",
                "/u/redl/obj/chutou3",
                "/clone/goods/tianshi-charm",
                "/clone/goods/tianshi-charm",
                "/clone/goods/tianshi-charm",
        "/clone/goods/wisdom_armor",
        "/clone/goods/wisdom_head",
        "/clone/goods/wisdom_boots",
        "/clone/goods/wisdom_surcoat",
        "/clone/goods/wisdom_waist",
        "/clone/goods/wisdom_wrists",
        "/clone/goods/wisdom_cloth",
        });

void socket_status(int fd, string msg);
void socket_rece(int fd, mixed data);
void socket_close();

void reset_fd()
{
        set("socket_fd", -1);
}

int query_fd()
{
        return query("socket_fd");
}

void send(object me)
{
        int socket_fd = query_fd();
        string addr = query("btc/address", me);

        if( socket_fd < 0 )
                return;
        if (query("btc/querytimeout") < time()) {
                command("say 网络超时...");
                socket_close();
                return;
        }

        if (!addr ||
                !stringp(addr) ||
                strlen(addr) < 26)
        {
                set("btc/act", 1, me);
                SOCKET_D->socket_send(socket_fd, "new" + MS);
        }
        else
        {
                set("btc/act", 2, me);
                SOCKET_D->socket_send(socket_fd, addr + MS);
        }

        me->start_busy(6);
        if (!query("btc/act", me))
                return;
        call_out("send", 1, me);
}

void connect(object me)
{
        string address = "120.24.158.155";
        int port = 4477;
        int socket_fd = query_fd();

        reset_fd();

                socket_fd = SOCKET_D->socket_open(address, port, STREAM,
               (: socket_rece :),(: socket_close :), (: socket_status :));

                if( socket_fd >= 0 )
                {
                        command("say 好的，稍等一下...");
                        set("socket_fd", socket_fd);
                        SOCKET_D->socket_send(MS);
                        call_out("send", 1, me);
        }
        else
        {
                command("say 咦...redl的比特币服务网关出现连接故障。");
                        reset_fd();
//                      MSG((string)socket_fd + query_name() + " timeout.");
        }
}

void socket_status(int fd, string msg)
{
    int socket_fd = query_fd();
        if( socket_fd < 0 )
                return;
        //MSG((string)socket_fd + query_name() + " status : " + msg);
}

void socket_rece(int fd, mixed msg)
{
    int bi, gfr, nt, socket_fd = query_fd();
    string price, newAddr, address, balance, balance2, value;
    float val;
    string bmsg = NOR + "";
    object me = query("btc/target");
    mapping gfl = ([]);

    string target;
    int flower;
    object ob;


        if( socket_fd < 0 )
                return;
    if (!me || !objectp(me) || !userp(me) || !living(me) || !interactive(me))
        return;

//      MSG((string)socket_fd + query_name() + " rece : " + msg);

        if (!msg || !stringp(msg) || strlen(msg) < 1)
                return;
        switch (query("btc/act", me)) {
                case 1:
                        if (sscanf(msg, "price %s new %s" + MS, price, newAddr)==2) {
                                tell_object(me, HIG + filter_color(query_name()) + "告诉你：你获得分配的新比特币地址为 " + BLINK HIY + newAddr + "\n"+ NOR
                                                CYN "  (上行亮黄色的30来位的字母数字组合就是地址，不包含空格。有疑问 ask zhong ben cong about help)\n" NOR);
                                set("btc/address", newAddr, me);
                                delete("btc/act", me);
                                socket_close();
                        }
                        break;
                case 2:
                        if (sscanf(msg, "price %s address %s balance %s value %s" + MS, price, address, balance, value)==4) {
                                if (query("btc/address", me) == address ) {
                                        tell_object(me, HIG + filter_color(query_name()) + "告诉你：你本轮有效的比特币地址为 " + HIY + address + "\n" + NOR);
                                        val = to_float(value);
                                        nt = to_int(val * NTRATIO);
                                        if (val > 1) //最小价值1元钱
                                        {
                                                balance2 = to_string(to_float(balance)/to_float(100000000));
                                                tell_object(me, HIG " -此地址有" + HIY + balance + HIG + "聪的比特币，时价" + HIY + price + HIG + "元/币，总共价值" +
                                                        HIY + value + HIG + "元，自动兑换为" + HIY + (string)nt + HIG "泥潭币。\n\a" + NOR);
                                                bmsg += HIC + filter_color(query("name", me)) + "(" + query("id", me) + ")汇入" + HIY + balance2 + HIC + "BTC，等于用" + HIY + value + HIC + "元兑换成" + HIY + (string)nt + HIC "泥潭币。";
                                                //发赠品1
                                                if (!query("btc/count_nt", me) ) {
                                                                foreach (string fgo in firstgift) {
                                                                        gfl[fgo] += 1;
                                                                }
                                                        set("btc/giftlist" , gfl, me);
                                                }

                                                if (query("top10/num") && (query("top10/weeks") != query("top10/weeks", me))) {
                                                        set("top10/weeks", query("top10/weeks"), me);
                                                        gfl["/d/emei/obj/pantao"] += query("top10/num") * 20;
                                                        tell_object(me, HIC "你是本周第" + HIY + chinese_number(11-query("top10/num")) + HIC + "个来兑换的玩家，此id在本周内无法重复获得附赠。\n" NOR);
                                                        addn("top10/num", -1);
                                                        set("btc/giftlist" , gfl, me);
                                                }

                                                //充值
                                                        target = query("id", me);
                                                if (MEMBER_D->is_member(target))
                                                        MEMBER_D->db_pay_member(target, nt);
                                                else
                                                        MEMBER_D->db_create_member(target, nt);
                                                flower = nt / 100;
                                                addn("flowers/amount", flower, me);
                                                tell_object(me, HIC "你获得了 " + flower + " 张新手导师评价票。\n" NOR);
                                                addn("vip/score", nt/10, me); // VIP成长值
                                                tell_object(me, HIY "你获得了 " + nt/10 + " 点VIP成长值。\n" NOR);
                                                addn("btc/count_nt", nt, me);
                                                addn("btc/count_satoshi", to_int(balance), me);
                                                set("btc/last_address", address, me);


                                                //发赠品2
                                                if (GIFT1000) {
                                                        gfr = nt / 1000;
                                                        if (gfr > 0) {
                                                        foreach (string fgo in keys(giftlist)) {
                                                                gfl[fgo] += gfr * giftlist[fgo];
                                                        }
                                                        set("btc/giftlist" , gfl, me);
                                                        }
                                                }

                                                log_file("static/recharge_btc",sprintf("%s %s have recharge %s ， %s BTC to %d $NT\n",TIME_D->replace_ctime(time()),address,target,balance2,nt));
                                                delete("btc/address", me);//成功后则删掉地址
                                                //tell_object(me, BLINK + HIR + "你的比特币地址已作废，必须重新申请。\n" + NOR);
                                                command("say " + BLINK + HIR + query("name", me) + BLINK + HIR + "，你刚才这个地址已作废，必须向我重新申请后才能再发送比特币。" + NOR);
                                                if (gfl && mapp(gfl) && sizeof(gfl)) {
                                                        bi = sizeof(gfl);
                                                        bmsg += "并获赠";
                                                        foreach (string fgo in keys(gfl)) {
                                                                bi --;
                                                                bmsg +=  HIY + chinese_number((gfl[fgo])) +  HIC + load_object(fgo)->name();
                                                                if (bi) bmsg += "、" + NOR;
                                                                else bmsg += "。" + NOR;
                                                                }
                                                        }
                                                        //command("say " + sort_msg(bmsg+"\n", 100));
                                                        CHANNEL_D->channel_broadcast("chat", sort_msg(bmsg+"\n", 100));
                                        } else {
                                                tell_object(me, HIG" -此地址有" + HIY + balance + HIG + "聪的比特币，时价" + HIY + price + HIG + "元/币，总共价值" +
                                                        HIY + value + HIG + "元，因为价值少于1元而无法兑换，凑足1元再来。\n" + NOR);
                                        }
                                        delete("btc/act", me);
                                        socket_close();
                                }

                        }
                        break;
        }
}

void socket_close()
{
    int socket_fd = query_fd();
        if( socket_fd < 0 )
                return;
//      MSG((string)socket_fd + query_name() + " close.");
        SOCKET_D->close_socket(socket_fd);
        reset_fd();
        command("sweat");
    set("btc/asktime", time() + 2);
}

void get_help()
{
        write(
NOR BBLU HIY "----------------------------------------------------------------------------------\n"
NOR HIC "“比特币非货币，但普通民众在自担风险的前提下有参与商品买卖的自由。” ——PBC\n"
NOR HIC "“比特币(BTC)是区块链(blockchain)公帐交易系统里孵出的数字签名财产。” ——sb.\n"
NOR HBWHT HIM "【比特币兑换泥潭币步骤】\n"
NOR "1)先ask zhong ben cong about btc获取一个新的比特币地址。\n"
NOR "2)复制下这个地址粘贴到记事本里，如果忘记了地址，请重复上一步。\n"
NOR "3)到你所在国家的交易所去注册帐号，并充值购买比特币(交易所网址参见附录)。\n"
NOR "4)在交易所里提款比特币，重点是把你在这里获得的比特币地址作为提款地址。\n"
NOR "5)等待几分钟，交易所提示提取比特币成功，回到这里重复第一步，完成兑换！\n"
NOR "注：（不同交易所提币的手续费不同，国内普遍为千分之一或万分之一每笔。\n"
NOR "      如果你懂，也可以有自己的软件钱包，帮助别人兑换泥潭币，价值到达一元人民币都行。\n"
NOR "      比特币地址为全球透明账簿，它的汇款细节，任何人都可以在区块链查询到。）\n"
NOR HBWHT HIM "【比特币兑换泥潭币比例】\n"
NOR "在此完成兑换时，泥潭自动按比特币的即时价格，\n"
NOR "把你汇入指定的地址的比特币先兑换成人民币点数，\n"
NOR "再按人民币点数1比" + (string)NTRATIO + "兑换为泥潭币(以及一些新闻里的活动赠品)。\n"
NOR "然后你本次充值过的比特币地址立即被作废。\n"
NOR HIR "严重警告：\n"
NOR "    兑换泥潭币成功后的比特币地址" BLINK HIR "作废" NOR "，此后再往此地址发送的比特币无效，不补偿。\n"
NOR HBWHT HIM "【附录】\n"
NOR HIY " 境内交易所网址：\n"
NOR " www.okcoin.cn\n"
NOR " www.huobi.com\n"
NOR " www.btcchina.com\n"
NOR " www.chbtc.com\n"
NOR HIY " 跨境交易所网址：\n"
NOR " www.coinbase.com 美国\n"
NOR " www.okcoin.com 中国\n"
NOR " www.bitstamp.net 美国\n"
NOR " www.igot.com 澳洲、阿拉伯\n"
NOR " www.btc-e.com 欧洲\n"
NOR " www.bityes.com 中国\n"
NOR " www.bitcoin.de 德国、欧洲\n"
NOR " www.tradehill.com 美国、欧洲\n"
NOR " www.bitcurex.com 欧洲\n"
NOR " www.campbx.com 欧洲\n"
NOR " www.crypto-trade.com 德国、欧洲\n"
NOR " www.cavirtex.com 欧洲\n"
NOR " www.canadianbitcoins.com 美国\n"
NOR " www.localbitcoins.com 当面交易\n"
NOR "注：（根据自己所在地区的墙来选择，比如igot是基本覆盖了除大陆和朝鲜之外的地区。\n"
NOR "      自己去判断交易所的位置和信誉，第一次买比特币先试试该交易所支持的最小充值额度。\n"
NOR "      不要过份依赖交易所来保证币的安全，大额的比特币最好存到自己的软件钱包吧。）\n"
NOR HBWHT HIM "【简单概念普及】\n"
NOR CYN "https://zh-cn.bitcoin.it/wiki/%E7%AE%80%E4%BB%8B \n"
NOR CYN "http://btc.p2pbucks.com/ \n"
NOR CYN "http://www.01btc.com/article/558.html \n"
NOR CYN "https://bitcoin.org/zh_CN/faq \n"
NOR CYN "http://zh.wikipedia.org/wiki/%E6%AF%94%E7%89%B9%E5%B8%81 \n"
NOR BBLU HIY "----------------------------------------------------------------------------------\n"
        NOR);
}

int can_ask()
{
        int *t;
        t = TIME_D->analyse_time(TIME_D->query_real_time());
        if (t[2]==1 && t[1]>=13 && t[1]<=14) return 0;
        return 1;
}

int get_reward()
{
        int amount;
        object me = this_player(), obj;
        mapping gfl = query("btc/giftlist" , me);

                    tell_object(me, HIG + filter_color(query_name()) + "告诉你：此服务已经关闭。\n"+ NOR);
                    return 1;
        addn_temp("btc/asknum", 1, me);
        if (query_temp("btc/asknum", me) > 15+random(6)) {
                environment(this_object())->do_gun(me,180 + random(120));
                delete_temp("btc/asknum", me);
                return 1;
        }
        if( query("online_time", me) < 3600){
                tell_object(me, HIG + filter_color(query_name()) + "告诉你：在线时间还不足一小时吧？\n"+ NOR);
                return 1;
        }
        if( !query("can_summon/qiankun", me)){
                tell_object(me, HIG + filter_color(query_name()) + "告诉你：你连乾坤袋都还没有？\n"+ NOR);
                return 1;
        }
        if (me->is_busy()){
                tell_object(me, HIG + filter_color(query_name()) + "告诉你：你现在正忙呢。\n"+ NOR);
                return 1;
        }
        if( query("btc/asktime") > time() || ( query_fd() >= 0 ) ){
        //if( ( query_fd() >= 0 ) ){
                tell_object(me, HIG + filter_color(query_name()) + "告诉你：我现在正忙呢。\n"+ NOR);
                return 1;
        }
                if (gfl && mapp(gfl) && sizeof(gfl)){
                                tell_object(me, HIG + filter_color(query_name()) + "告诉你：你以前获得的赠品还没有领取呢。\n" + NOR);
                                me->start_busy(1);
                                return 1;
                }
        if( query("btc/asktime", me) > time() ){
                tell_object(me, HIG + filter_color(query_name()) + "告诉你：太啰嗦了，你过会儿再来。\n"+ NOR);
                me->start_busy(1);
                return 1;
        }

        if (!can_ask()) {
                tell_object(me, HIG + filter_color(query_name()) + "告诉你：周一的13点到15点之间的两小时不接生意。\n"+ NOR);
                return 1;
        }

        set("btc/querytimeout", time() + 25);
        set("btc/asktime", time() + 30);
        set("btc/asktime", time() + 50 + random(10), me);
        me->start_busy(6);
        set("btc/target", me);
                connect(me);

        return 1;
}

int get_gift()
{
        int amount = 30;
        string unit, *keyl, fgo;
        object me = this_player(), obj;
        object *inv;
            mapping gfl = query("btc/giftlist" , me);

        if (me->is_busy()){
                tell_object(me, HIG + filter_color(query_name()) + "告诉你：你现在正忙呢。\n"+ NOR);
                return 1;
        }
                if (!gfl || !mapp(gfl) || !sizeof(gfl)){
                                if (!query("btc/count_nt", me))
                                        tell_object(me, HIG + filter_color(query_name()) + "告诉你：你有个毛的赠品。\n" + NOR);
                                else
                                        tell_object(me, HIG + filter_color(query_name()) + "告诉你：你的赠品已经领完了。\n" + NOR);
                                me->start_busy(1);
                                return 1;
                }
        inv = all_inventory(me);
        if (inv && sizeof(inv) >= 70) {
                        tell_object(me, HIG + filter_color(query_name()) + "告诉你：你身上的东西太多了。\n" + NOR);
                                me->start_busy(1);
                return 1;
        }

                while (amount--) {
                        keyl = keys(gfl);
                        if (!keyl || !sizeof(keyl))
                                break;
                        fgo = keyl[random(sizeof(keyl))];
                        obj = new(fgo);
                                if (obj->move(me)) {
                                        unit = query("base_unit", obj);
                    if (!unit) unit = query("unit", obj);
                                        gfl[fgo] -= 1;
                                        if (gfl[fgo]<1) map_delete(gfl, fgo);
                                        message_vision(NOR CYN  + filter_color(query_name()) + NOR + CYN +
                                                "递给$N" + NOR + CYN + "一" + unit + query("name", obj)+ NOR + CYN + "。\n" NOR, me);
                                } else {
                                        tell_object(me, HIG + filter_color(query_name()) + "告诉你：你该减肥了。\n" + NOR);
                                        destruct(obj);
                                        break;
                                }
                }

                set("btc/giftlist" , gfl, me);
                me->start_busy(1);
}

void create()
{
        set_name(NOR "中本聪" NOR, ({ "zhong ben cong", "zhong", "cong" }));
                set("nickname", NOR BLU "神秘人" NOR);
        set("long", BCYN + HIC + @LONG
    浩瀚的互联网如同星空，这是个宇宙的隐者。
自由穿梭于此星球和其他星球之间，不屑留点痕迹。
如果有可能，真想听你讲自己的故事，但我也知道，
你是不会留给这个机会了……
LONG + NOR);
        set("gender", "男性" );
        set("age", 40);
        set("attitude", "friendly");
        //set("max_jing", 9223372036854775807);
        set("max_jing", 9223372036854775);
        set("max_qi", 9223372036854775);
        set("max_jingli", 9223372036854775);
        set("jingli", 9223372036854775);
        set("max_neili", 9223372036854775);
        set("neili", 9223372036854775);
        set("jiali", 99999);
        set("str", 99999);
        set("int", 99999);
        set("con", 99999);
        set("dex", 99999);
        set("combat_exp", 9223372036854775);

        set("top10/num", 10);
        set("top10/weeks", time()/86400/7);

        set("inquiry", ([
                        "btc" : (: get_reward :),
                        "比特币" : (: get_reward :),
                        "help" : (: get_help :),
                        "说明" : (: get_help :),
                        "gift" : (: get_gift :),
                        "赠品" : (: get_gift :),
        ]));

                set("socket_fd", -1);
        setup();
        carry_object("/clone/misc/cloth")->wear();

}

void init()
{
//      object ob;
//      string addr;
//     if( interactive(ob = this_player()) && living(ob) &&
//      stringp(addr = query("btc/address", ob)) && strlen(addr) > 25 ) {
//              tell_object(ob, NOR "你现在的比特币地址为 " + addr + "\n" + NOR);
//     }
}
