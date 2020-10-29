// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "这是武当二号的火麒麟兽，个头不小。[2;37;0m
它是武当二号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kimiw");
        set("owner_name", "武当二号");
        set_temp("owner", "kimiw");
        set_temp("owner_name", "武当二号");
        ::setup();
}
