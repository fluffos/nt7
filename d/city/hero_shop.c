
// This program is a part of NT MudLIB

inherit ROOM;
#define SALE_D  "/adm/daemons/saled"

void create()
{
        set("short", "英雄商店");
        set("long", @LONG
这里是英雄商店，没有店铺的玩家可以在这里寄售物品，价格以
王者金币(NT)作为单位，店里挂着一个醒目的牌子(paizi)。
LONG );
        set("region", "yangzhou");
        set("exits", ([
                "north" : __DIR__"majiu",
        ]));
        set("item_desc", ([
                "paizi" : @TEXT
     本商店提供以下服务：
      寄售        stock
      取回        unstock
      察看        list
      购买        buy
TEXT
        ]) );

        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", 30);
        set("coor/y", -10);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_stock", "stock");
        add_action("do_unstock", "unstock");
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

int do_stock(string arg)
{
        write(SALE_D->do_stock(this_player(), arg));
        return 1;
}

int do_unstock(string arg)
{
        write(SALE_D->do_unstock(this_player(), arg));
        return 1;
}

int do_list(string arg)
{
        this_player()->start_more(SALE_D->do_list(this_player(), arg));
        return 1;
}

int do_buy(string arg)
{
        write(SALE_D->do_buy(this_player(), arg));
        return 1;
}

