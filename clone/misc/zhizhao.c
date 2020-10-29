// vendor_pass.c 商业执照

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("商业执照", ({ "shangye zhizhao", "zhizhao" }) );
        set_weight(1);
        if( clonep() )
        set("long", "一张红底金边帖子，上面写着四个金灿灿的大字：商业执照，左下角是黄真的亲笔签名。\n");
        set("unit", "份");
        set("value", 0);
        set("material", "paper");
        set("no_get",1);
        set("no_give",1);
        set("no_sell",1);
        setup();
}

void init()
{
       add_action("do_bantan", "baitan");
       add_action("do_shoutan","shoutan");
       add_action("do_stock","stock");
       add_action("do_unstock","unstock");
}

int do_bantan()
{
        object obj,me;
        obj = this_object();
        me = this_player();

        if( !query("is_vendor", me))return notify_fail("你又不是商人，瞎折腾什么啊！\n");
        if (!present("shangye zhizhao",me)) return notify_fail("你的商业执照不在身上，难道想无证搬摊？\n");
        if( query_temp("on_bantan", me))return notify_fail("你已经占了一个摊位，还想怎的？\n");

        message_vision(HIW "$N找了一块空地，一屁股坐了下来，随后掏出一块布摊开在地。\n" +NOR,me);
        tell_object(me,HIW "现在你可以摆上(stock)货物了，你也可以收起(unstock)某种货物。\n");
        set_temp("on_bantan", 1, me);
        delete("vendor_goods", me);
        return 1;
}

int do_shoutan()
{
        object obj,me;
        obj = this_object();
        me = this_player();

        if( !query("is_vendor", me))return notify_fail("你又不是商人，瞎折腾什么啊！\n");
        if (!present("shangye zhizhao",me)) return notify_fail("你的商业执照不在身上，请退线后重新连线并申请一个新的。\n");
        if( !query_temp("on_bantan", me))return notify_fail("你并没有摆摊，哪里来的摊子给你收啊？\n");

        message_vision(HIW "$N提起摊布的四个角，把货物一股脑的收了起来，站起身来。\n" +NOR,me);
        delete_temp("on_bantan", me);
        delete("vendor_goods", me);
        return 1;
}

int do_stock(string arg)
{
        object obj,me,goods;
        int amount,value,i;
        mapping all_goods;
        string beishu,*args;
        
        me = this_player();
        if( !query("is_vendor", me))return notify_fail("你又不是商人，瞎折腾什么啊！\n");
        if (!present("shangye zhizhao",me)) return notify_fail("你的商业执照不在身上，请退线后重新连线并申请一个新的。\n");
        if( !query_temp("on_bantan", me))return notify_fail("你必须首先摆一个摊位(baitan)才能放货物！\n");
        if (!arg) return notify_fail("stock <货物> n (其中n可以是1、2、3、4、5，表示该货物原价值的n倍，缺省的话表示半价)\n");

        i = sizeof(args = explode(arg, " "));

        i--;
        if (!sscanf(args[i], "%d", amount)) 
                amount = 0;
        else arg = replace_string(arg," "+amount,"");

        if (!(goods = present(arg,me)) || !objectp(goods)) return notify_fail("你身上并没有这个货物啊！\n");
        if (goods->is_character()) return notify_fail("你不能贩卖人口！\n");
        if( query("money_id", goods))return notify_fail("你疯了？钱也拿来出售？\n");

        if( sizeof(query("vendor_goods", me)) >= 18)return notify_fail("你一次只能摆上十八种货物，请首先收起几种货物再摆上这种货物。\n");
        if (amount>5) return notify_fail("你最多以原价五倍出售，不要太心黑啦！\n");

        value=query("base_value", goods);
        if( !value)value=query("value", goods);
        if (amount)
        { 
                value = amount * value;
                beishu = (string)amount + "倍价";
        }
        else
        {
                value = value/2;
                beishu = "半价";
        }
        if (!value) return notify_fail("这种不值钱的烂货你也想摆上？太没有商业道德啦！\n");

        all_goods=query("vendor_goods", me);
        if (!all_goods) all_goods = ([ ]);
        all_goods[base_name(goods)] = value;
        set("vendor_goods", all_goods, me);
        message_vision(HIW "$N将"+ NOR + goods->name(1) + HIW +"标上" + HIY + beishu + HIW"摆上摊子开始出售。\n"NOR,me);
        return 1;
}

int do_unstock(string arg)
{
        object obj,me,goods;
        int i,amount,value,have_it = 0;
        mapping all_goods;
        string *goods_key,beishu;
        
        me = this_player();
        if( !query("is_vendor", me))return notify_fail("你又不是商人，瞎折腾什么啊！\n");
        if (!present("shangye zhizhao",me)) return notify_fail("你的商业执照不在身上，请退线后重新连线并申请一个新的。\n");
        if( !query_temp("on_bantan", me))return notify_fail("你连摊子都没有搬，还想收起货物？\n");
        if (!arg) return notify_fail("unstock <货物>\n");

        if (!(goods = present(arg,me))) return notify_fail("你现在并没有这个货物！\n");
        all_goods=query("vendor_goods", me);
        if (!all_goods) return notify_fail("你现在还没有摆上任何货物！\n");

        goods_key = keys(all_goods);
        for (i = 0;i < sizeof(goods_key);i++)
        {
                if (base_name(goods) == goods_key[i]) have_it = 1;
        }

        if (have_it) 
        {
                map_delete(all_goods,base_name(goods));
                message_vision(HIW "$N将" + NOR + goods->name(1) + HIW + "从摊子上收起不卖了。\n",me);
        } else return notify_fail("你没有把这样货物摆上摊子出售啊。\n");

        set("vendor_goods", all_goods, me);
        return 1;
}

int query_autoload() { return 1; } 