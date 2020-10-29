// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("仙女[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "好东东[2;37;0m
它是梦回武当的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wdaa");
        set("owner_name", "梦回武当");
        set_temp("owner", "wdaa");
        set_temp("owner_name", "梦回武当");
        ::setup();
}
