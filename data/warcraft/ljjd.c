// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m轰炸机[2;37;0m[2;37;0m", ({"hzj"}));        
        set("gender", "男性");                
        set("long", "金色轰炸机[2;37;0m
它是段了么的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ljjd");
        set("owner_name", "段了么");
        set_temp("owner", "ljjd");
        set_temp("owner_name", "段了么");
        ::setup();
}
