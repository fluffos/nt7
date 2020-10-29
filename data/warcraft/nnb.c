// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小眼[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "小眼[2;37;0m
它是哈拉咪咪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nnb");
        set("owner_name", "哈拉咪咪");
        set_temp("owner", "nnb");
        set_temp("owner_name", "哈拉咪咪");
        ::setup();
}
