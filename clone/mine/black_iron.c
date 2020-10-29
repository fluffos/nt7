// black_iron.c
// 玄铁

#include <mine_def.h>

inherit ITEM;

protected int sum;

string query_long();

int is_iron_class_res() { return 1; }
string query_mine_class() { return BLACK_IRON; }
int query_mine_value();

int query_sum() { return sum; }
void add_sum(int n)
{
        sum += n;
        if(sum < 0)
                sum = 0;
}

int set_sum(int n)
{
        if(n < 1)
                return 0;
        sum = n;
        return 1;
}

void create(int arg)
{
        set_name("玄铁", ({ "black iron ingot" }) );
        set_weight(1000);

        if(intp(arg) && (arg > 0))
                sum = arg;

        set("value", evaluate((: query_mine_value :),this_object()) );
        set("unit", "块");
        set("long", evaluate((: query_long :), this_object()));
}

int query_mine_value()
{
        return MINE_D->query_mine_class_value(BLACK_IRON)*sum;
}

string query_selling_msg()
{
        if(sum < 1)
                return "一钱不值";
        else
                return sprintf("%d 两重", sum);
}

string query_long()
{
        string l = "这是一块玄铁，";

        if(sum < 1)
                l += "看起来\n一钱不值。\n";
        else
                l += sprintf("大约\n有 %d 钱重。\n", sum);

        return l;
}

int query_save_args()
{
        return sum;
}