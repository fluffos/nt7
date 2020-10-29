// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m金翅大鹏鸟[2;37;0m[2;37;0m", ({"hots"}));        
        set("gender", "女性");                
        set("long", "dfd[2;37;0m
它是乐橙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hot");
        set("owner_name", "乐橙");
        set_temp("owner", "hot");
        set_temp("owner_name", "乐橙");
        ::setup();
}
