// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m九[1;36m头[1;34m鸟[2;37;0m[2;37;0m", ({"winds"}));        
        set("gender", "男性");                
        set("long", "$HIW$九$HIC$头$HIB$鸟[2;37;0m
它是疾风的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ajax");
        set("owner_name", "疾风");
        set_temp("owner", "ajax");
        set_temp("owner_name", "疾风");
        ::setup();
}
