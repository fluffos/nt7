// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"yitian"}));        
        set("gender", "女性");                
        set("long", "这就是四神兽之一的朱雀。[2;37;0m
它是虚拟人的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dammy");
        set("owner_name", "虚拟人");
        set_temp("owner", "dammy");
        set_temp("owner_name", "虚拟人");
        ::setup();
}
