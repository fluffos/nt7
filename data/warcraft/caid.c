// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m输入文字中[2;37;0m[2;37;0m", ({"bmw"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是菜的的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "caid");
        set("owner_name", "菜的");
        set_temp("owner", "caid");
        set_temp("owner_name", "菜的");
        ::setup();
}
