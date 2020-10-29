// /adm/daemons/pawn_d.c
// by Find.

/*
单项记录格式：
({"find","/obj/book/guwen_book",933947068,"/d/chang/hockshop","这是"})
   ID     pawned ob             到期时间   当铺物件            stamp long
*/

/* 此功能需要对所有的典当物件进行管理和经常性的检索操作
 * 对系统资源（CPU & 记忆体）都有很大的消耗，每个玩家所
 * 能典当的物品总数应有限制，还有举行拍卖大会的时间间隔，
 * 间隔越大负担越重，目前暂定为每星期3、6晚八点举行，以
 * 后如必要可改为每星期2、4、6晚举行。
 * config 里的 maximum array size 也应足够大，目前暂设
 * 为 50000。
*/

/* 为统一货币单位、直观利于玩家出价参加竞买，所有显示价
 * 值均转换成整数银两的阿拉伯数字
 */
#define PAWN_STAMP        "/std/room/obj/pawn_stamp"

#include <ansi.h>

inherit F_DBASE;

protected string *all;

protected int max_item_limit = 5;        /* 玩家可典当物品的最大数目 */
protected int be_in_sale_meeting = 0;
protected int min_can_sale_num = 5;        /* 召开拍卖大会所要求的最少的死当物品数量 */

protected void begain_sale_meeting();
protected int find_next_object();
protected void end_sale_meeting();
protected int num_during_meeting = -1;        /* 拍卖大会过程中的物品编号 */
protected object current_object;                /* 正在拍卖的当前物品 */
protected int current_value = 0;                /* 当前价格 */
protected object current_user;                /* 正在出价的玩家 */
protected int min_value_per_chu;                /* 每次加价的最小值 */
protected int unvalid_flag = 0;                /* 当前是否可以出价 */

protected int call_interval = 5;                /* 每次喊价之间的间隔 */
protected int COST = 5;                        /* 拍卖起价折扣 */

void create()
{
        seteuid(getuid());
        set("channel_id", "典当精灵");
}

/* 玩家 login 时由此函数制造当票 */
void restore_players_pawnstamp(object me)
{
        mixed *user_objs;
        object stamp;

        if(!objectp(me) || !userp(me))
                return;

        // 拍卖会期间不处理
        if(be_in_sale_meeting)
                return;

        user_objs = DATABASE_D->query_user_all_pob(geteuid(me));

        if(!user_objs || !sizeof(user_objs))
                return;

        for(int i=0;i<sizeof(user_objs);i++)
        {
                stamp = new(PAWN_STAMP);
                if(!stamp)
                        continue;
                stamp->use_this_stamp(user_objs[i]);
                stamp->move(me);
        }
}

/* 返回一个玩家已典当的所有物品的数量是否已超过最高限 */
int can_pawn_ob(string id)
{
        if(!stringp(id) || id == "")
                return 0;
        else
                return (DATABASE_D->query_count_user_pob(id) < max_item_limit);
}

/* 典当一个物品。
 * return 0        出现错误
 * return -1        已达到了玩家可典当物品的最大数目
 * return 1        成功
 */
int pawn_one_object(object stamp)
{
        if(!objectp(stamp) || !stamp->is_pawn_stamp())
                return 0;

        if(!can_pawn_ob( stamp->query_master() ))
                return -1;

        return DATABASE_D->pawn_one_object( stamp->query_all_msg() );
}

/* 赎回一个物品。
 * return 0        出现错误
 * return -1        没有典当过这个物品
 * return 1        成功
 *
 * 此函数没有进行是否已过期检查。
 * 主要留待于另一个想法：
 * 目前物品过期就不能再赎回了，只能拍卖大会上见，
 * 过期检查在 HOCKSHOP 物件里。
 * 是否可以物品在过期后与上拍卖大会前的一段时间里
 * 还可赎回，不过要用两倍的价格买回作为惩罚？
 * 如这样 HOCKSHOP 里要作相应的修改，return -1
 * 也具有了不同的意义---即：已卖出。
 * restore_players_pawnstamp 函数里对过期的当票也
 * 应交付玩家，可以把当票名称改成“过期的当票”。
 * 是否如此有待于讨论。
 */
int redeem_one_object(object stamp)
{
        if(!objectp(stamp) || !stamp->is_pawn_stamp())
                return 0;

        return DATABASE_D->retrieve_one_object(stamp->query_master(),stamp->query_rtime());
}

// 以下为拍卖大会部分：
void touch_meeting()
{
        object selling_room;

        if(!previous_object() || (geteuid(previous_object()) != ROOT_UID))
                return;

        if(be_in_sale_meeting)
                return;
        else
        {
                if(selling_room = find_object("/d/changan/selling_room"))
                        selling_room->begin_paimai_meeting();
                be_in_sale_meeting = 1;
                begain_sale_meeting();
                return;
        }
}

protected int can_begain_meeting()
{
        all = DATABASE_D->query_all_exceed_pob();
        return sizeof(all) >= min_can_sale_num;
}

protected void begain_sale_meeting()
{
        int year = NATURE_D->query_year();

        if(!can_begain_meeting())
        {
                CHANNEL_D->do_channel( this_object(), "paimai",sprintf("◆%s创世%s年度全国拍卖大会通告◆："+
                "本届拍卖大会由于死当物品过少，决定取消！！",MUD_NAME,(!year)?"元":chinese_number(year)));
                be_in_sale_meeting = 0;
                return;
        }

        CHANNEL_D->do_channel( this_object(), "paimai",sprintf("%s创世%s年度全国拍卖大会现在开幕！"+
                "欢迎各界人士参加竞买！！",MUD_NAME,(!year)?"元":chinese_number(year)));
        call_out("teach_rules",2);
        return;
}

protected void teach_rules()
{
        CHANNEL_D->do_channel( this_object(), "paimai",
                      "参加竞买人士可以使用 chu <银两数> 命令对当前拍卖物品出价，\n"+
        "              表示你愿意出多少两银子购买当前拍卖物品。\n");
        call_out("lasting_sale_objs",5,0);
}

protected void reset_variable()
{
        current_object = 0;                /* 正在拍卖的当前物品 */
        current_value = 0;                /* 当前价格 */
        current_user = 0;                /* 正在出价的玩家 */
        min_value_per_chu = 0;                /* 每次加价的最小值 */
}

protected void give_obj_to_user()
{
        int cant_hold_flag;

        CHANNEL_D->do_channel( this_object(), "paimai",sprintf("恭喜%s(%s)以 %d 两银子购得 %s"+HIY+"。\n",
                query("name", current_user),geteuid(current_user),
                (current_value/100),current_object->name()));

        if(pay_from_bank(current_user,current_value))
        {
                if(!current_object->move(current_user))
                {
                        cant_hold_flag = 1;
                        current_object->move(environment(current_user));
                }

                tell_object(current_user,sprintf("一个小伙计满头大汗地跑到你跟前说道：“这是您买的东西%s。”\n",
                        (cant_hold_flag)?"给您放地上了":"您收好" ));
        }
        else
                tell_object(current_user,"你的银行存款不够！\n");

        delete_temp("be_in_sale_meeting_chu", current_user);

        reset_variable();
}

protected void lasting_sale_objs(int when)
{
        int value;

        remove_call_out("lasting_sale_objs");

        if(num_during_meeting == -1) // 还未开始拍卖
        {
                num_during_meeting = 0;
                find_next_object();
                if( !value=query("value", current_object) )
                        value = current_object->value();
                current_value = to_int(ceil(value/10*COST/100))*100;
                min_value_per_chu = to_int(ceil(value/1000))*100;
                CHANNEL_D->do_channel( this_object(), "paimai","大会正式开始，第一件物品：\n"+
                        sprintf("             %s"+HIY+"一%s，原价 %d 两白银：，起价：%d 两白银\n"+
                                "             每次出价至少要高于当前价格 %d 两白银，请有意者出价。\n",
                                current_object->name(),(query("unit", current_object))?
                                query("unit", current_object):"件",to_int(ceil(value/100)),
                                (current_value/100),(min_value_per_chu/100)));
                unvalid_flag = 0;
                call_out("lasting_sale_objs",call_interval+2,0);
                return;
        }

        if(!when)        // 新价格或者新物品出来后进行一次询问
        {
                CHANNEL_D->do_channel( this_object(), "paimai",
                        sprintf("%s"+HIY+"当前价格：%d 两白银，%s？\n",current_object->name(),
                        (current_value/100),
                        (current_user)?"还有人出更高的价格吗":"有人对这个价格感兴趣吗"));
                call_out("lasting_sale_objs",call_interval,1);
                return;
        }

        if(when == 1)        // 第一次计数
        {
                CHANNEL_D->do_channel( this_object(), "paimai",
                        sprintf("当前物品：%s"+HIY+"，%d 两白银 第一次！有兴趣的快出价啦！\n",current_object->name(),
                        (current_value/100)));
                call_out("lasting_sale_objs",call_interval,2);
                return;
        }

        if(when == 2)        // 第二次计数
        {
                CHANNEL_D->do_channel( this_object(), "paimai",
                        sprintf("当前物品：%s"+HIY+"，%d 两白银 第二次！机会难得呀！\n",current_object->name(),
                        (current_value/100)));
                call_out("lasting_sale_objs",call_interval,3);
                return;
        }

        if(when == 3)
        {
                unvalid_flag = 1;
                if(current_user)
                        give_obj_to_user();
                else
                        reset_variable();
                if(!find_next_object())
                {
                        end_sale_meeting();
                        return;
                }
                else
                {
                        if( !value=query("value", current_object) )
                                value = current_object->value();
                        current_value = to_int(ceil(value/10*COST/100))*100;
                        min_value_per_chu = to_int(ceil(value/1000))*100;
                        CHANNEL_D->do_channel( this_object(), "paimai","继续进行下一件物品：\n"+
                                sprintf("             %s"+HIY+"一%s，原价 %d 两白银：，起价：%d 两白银\n"+
                                "             每次出价至少要高于当前价格 %d 两白银，请有意者出价。\n",
                                current_object->name(),(query("unit", current_object))?
                                query("unit", current_object):"件",(value/100),
                                (current_value/100),(min_value_per_chu/100)));
                        unvalid_flag = 0;
                        call_out("lasting_sale_objs",call_interval+2,0);
                        return;
                }
        }
}

/*
 * return 0 已没有可拍卖的物品了
 * return 1 找到下一个可拍卖的物品
 */
protected int find_next_object()
{
        while(1)
        {
                if(num_during_meeting >= sizeof(all))
                        return 0;

                current_object = new(all[num_during_meeting]);
                if(!objectp(current_object))
                        all -= ({ all[num_during_meeting] });
                else
                {
                        num_during_meeting++;
                        return 1;
                }
        }
}

protected void end_sale_meeting()
{

        CHANNEL_D->do_channel( this_object(), "paimai","本届拍卖大会圆满结束。");

        all = 0;
        num_during_meeting = -1;
        be_in_sale_meeting = 0;
}

int query_being_meeting()
{
        return be_in_sale_meeting;
}

int query_num_during_meeting()
{
        return num_during_meeting;
}

int query_unvalid_flag()
{
        return unvalid_flag;
}

object query_current_user()
{
        return current_user;
}

int query_current_value()
{
        return current_value;
}

int query_min_value_per_chu()
{
        return min_value_per_chu;
}

/* 接受玩家的出价 */
void accept_chujia(object usr,int value)
{
        if(!usr || (current_user == usr))
                return;

        if(find_call_out("lasting_sale_objs"))
                remove_call_out("lasting_sale_objs");

        if(objectp(current_user))
                delete_temp("be_in_sale_meeting_chu",1, current_user);

        current_user = usr;
        current_value = value;

        CHANNEL_D->do_channel( this_object(), "paimai",
                sprintf("%s(%s)出价 %d 两白银竞买 %s"+HIY+"。\n",
                query("name", current_user),geteuid(current_user),
                current_value/100,current_object->name()));

        call_out("lasting_sale_objs",call_interval,0);
        return;
}