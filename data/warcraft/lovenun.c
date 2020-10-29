// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m王语嫣[2;37;0m[2;37;0m", ({"mlove"}));        
        set("gender", "女性");                
        set("long", "这便是传说中的神仙姐姐王姑娘王语嫣[2;37;0m
它是段玉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lovenun");
        set("owner_name", "段玉");
        set_temp("owner", "lovenun");
        set_temp("owner_name", "段玉");
        ::setup();
}
