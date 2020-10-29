// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m玉字二号丸[2;37;0m[2;37;0m", ({"yqc"}));        
        set("gender", "男性");                
        set("long", "kjkdleqewqewqewq[2;37;0m
它是诸葛玉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yucqing");
        set("owner_name", "诸葛玉");
        set_temp("owner", "yucqing");
        set_temp("owner_name", "诸葛玉");
        ::setup();
}
