inherit ITEM;
inherit F_FOOD;

void create()
{
        int i;
        string *names = ({ "石斑鱼", "虎纹鱼", "鲇鱼" });
        i = random(3);
        set_name(names[i], ({ "fish" }) );
        set_weight(120);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一条刚刚钓上来的鲜鱼。\n");
                set("unit", "条");
                set("value", 150);
                set("food_remaining", 3);
                set("food_supply", 60);
        }
}