// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "一只麒麟[2;37;0m
它是丁君辉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "emsb");
        set("owner_name", "丁君辉");
        set_temp("owner", "emsb");
        set_temp("owner_name", "丁君辉");
        ::setup();
}
