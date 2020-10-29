// tuijianxin-5.c 推荐信 王-使者

inherit ITEM;

void create()
{
        set_name("推荐信", ({"tuijian xin5", "xin4", "letter5"}));
        set_weight(100);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "封");
                set("long","这是一封护教法王为你写的推荐信，凭此可去见光明使者。\n");
                set("material", "paper");
        }
}