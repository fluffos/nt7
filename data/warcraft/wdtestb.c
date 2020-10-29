// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m验当武[2;37;0m[2;37;0m", ({"westtestbb"}));        
        set("gender", "男性");                
        set("long", "阿[2;37;0m
它是武当验的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wdtestb");
        set("owner_name", "武当验");
        set_temp("owner", "wdtestb");
        set_temp("owner_name", "武当验");
        ::setup();
}
