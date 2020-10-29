#include <ansi.h> 
inherit ITEM;

void create()
{
        set_name("录音带", ({ "tape" }) );
        set_weight(2);
        set("no_get", 1);
        set("no_put", 1);
        set("value",10);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "个");
                set("long", "录音带。\n");
                set("value", 1);
        }
        setup();
} 

void play_sound_0(object speaker,int index) {
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一说道：我乃当今三清宫掌门丁乘风的师叔......\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一说道：近来此处墓园发生异变，我带领门下弟子来察看，不想遭遇不测......\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一说道：这个墓园深处里有一处聚灵法阵，其下镇压了一个上古血魔。\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),CYN"丁一说道：我等发现，无数死灵已经从法阵中逃逸，血魔亦有脱困的迹象。\n"NOR);
                        break;
                case(4):
                        tell_room(environment(),CYN"丁一说道：就在我们重新布置法阵的时候，一群少林和尚杀了过来。\n"NOR);
                        break;
                case(5):
                        tell_room(environment(),CYN"丁一说道：这些和尚一定是受到了血魔的诅咒，丧心病狂了。\n"NOR);
                        break;
                case(6):
                        tell_room(environment(),CYN"丁一说道：我们两方斗了个两败俱伤，弟子们拚死保护我，如今只剩我一个重伤逃离至此......\n"NOR);
                        break;
                case(7):
                        tell_room(environment(),YEL"丁一呜呜的哭起来......\n"NOR);
                        break;
                case(8):
                        tell_room(environment(),CYN"丁一说道：你可愿意帮我们对付血魔？(accept yes/no)\n"NOR);
                        set_temp("开场白结束", 1, speaker);
                        break;
                default: 
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;

        }
        call_out("play_sound_0",1,speaker,++index);
}

void play_sound_1(object speaker,int index) {
        object mazeobj;
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一说道：嗯......多谢......\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一说道：血魔实在是法力无边......他最擅长诱惑......我已经分不清敌我！\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一说道：就请你证明尚未被血魔诱惑: 杀八个骷髅，八个幽灵，八个僵尸。\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),CYN"丁一说道：完成后再来找我(report)。\n"NOR);
                        set_temp("任务", 1, speaker);
                        break;
                default: 
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 1, mazeobj);
                                set("quest/quest_name", "证明忠诚", mazeobj);
                                set("quest/quest_desc", "杀八个骷髅，八个幽灵，八个僵尸", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                set("quest/to_kill/骷髅", 8, mazeobj);
                                set("quest/to_kill/幽灵", 8, mazeobj);
                                set("quest/to_kill/僵尸", 8, mazeobj);
                        }
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
        }
        call_out("play_sound_1",1,speaker,++index);
}

void play_sound_2(object speaker,int index) {
        object mazeobj;
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一说道：好...做得不错!\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一说道：想要挑战血魔, 先要了解血魔的能力......\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一说道：这个墓园有很多血魔的手下......他的每个手下代表了他的一种能力！\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),CYN"丁一说道：去尝试着杀掉三个骷髅武士，三个骷髅法师，三个幽灵之眼，三个幽灵之火，三个血僵尸，和三个尸煞。\n"NOR);
                        break;
                case(4):
                        tell_room(environment(),CYN"丁一说道：完成后再来找我(report)。\n"NOR);
                        set_temp("任务", 2, speaker);
                        break;
                default: 
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                delete("quest/to_kill", mazeobj);
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 2, mazeobj);
                                set("quest/quest_name", "证明实力", mazeobj);
                                set("quest/quest_desc", "杀三个骷髅武士，三个骷髅法师，三个幽冥之眼，三个幽冥之火，三个血僵尸，三个尸煞", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                set("quest/to_kill/骷髅武士", 3, mazeobj);
                                set("quest/to_kill/骷髅法师", 3, mazeobj);
                                set("quest/to_kill/幽冥之眼", 3, mazeobj);
                                set("quest/to_kill/幽冥之火", 3, mazeobj);
                                set("quest/to_kill/血僵尸", 3, mazeobj);
                                set("quest/to_kill/尸煞", 3, mazeobj);
                        }
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
        }
        call_out("play_sound_2",1,speaker,++index);
}

void play_sound_3(object speaker,int index) {
        object mazeobj;
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一说道：做得很好!\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一说道：你有这样的实力我就放心了！\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一说道：去找到那些堕落的少林和尚，杀了他们。他们手中有个法器，可以对付血魔。\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),CYN"丁一说道：完成后再来找我(report)。\n"NOR);
                        set_temp("任务", 3, speaker);
                        break;
                default: 
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                delete("quest/to_kill", mazeobj);
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 3, mazeobj);
                                set("quest/quest_name", "排除异己", mazeobj);
                                set("quest/quest_desc", "杀少林和尚，取得法器", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                set("quest/to_kill/心武", 1, mazeobj);
                                set("quest/to_find/聚灵塔", 1, mazeobj);
                        }
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
        }
        call_out("play_sound_3",1,speaker,++index);
}

void play_sound_4(object speaker,int index) {
        object mazeobj;
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一说道：太好了!可恶的和尚，跟我争......哈哈.....哦...那个...咳咳...\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一说道：启动聚灵法阵需要一些阴气较盛的东西为引，\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一说道：巫妖的骨杖，幽冥魔的幽冥之火，僵尸王的僵尸血，各取一样来！\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),CYN"丁一说道：完成后再来找我(report)。\n"NOR);
                        set_temp("任务", 4, speaker);
                        break;
                default: 
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                delete("quest/to_kill", mazeobj);
                                delete("quest/to_find", mazeobj);
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 4, mazeobj);
                                set("quest/quest_name", "寻找法引", mazeobj);
                                set("quest/quest_desc", "找到巫妖的骨杖，幽冥魔的幽冥之火，僵尸王的僵尸血各一样", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                set("quest/to_find/骨杖", 1, mazeobj);
                                set("quest/to_find/幽冥之火", 1, mazeobj);
                                set("quest/to_find/僵尸血", 1, mazeobj);
                        }
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
        }
        call_out("play_sound_4",1,speaker,++index);
}

void play_sound_5(object speaker,object leader,int index) {
        object mazeobj;
        if(!environment())
                return;
        if(!speaker)
                return;
        if(!leader) {
                delete_temp("in_speech", speaker);
                destruct(this_object());
                return;
        }
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一说道：这样所有需要的法器就全了！\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一说道：我们到聚灵法阵那里，我来作法，重新召唤...哦不，重新封印血魔！\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一说道：法阵那里可能还有些血魔的手下......你从前面带路吧！\n"NOR);
                        set_temp("任务", 5, speaker);
                        break;
                default: 
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                delete("quest/to_find", mazeobj);
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 5, mazeobj);
                                set("quest/quest_name", "清理法阵", mazeobj);
                                set("quest/quest_desc", "把丁一带到聚灵法阵，并清理那里的血魔手下", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                speaker->set_leader(leader);
                        }
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
        }
        call_out("play_sound_5",1,speaker,leader,++index);
}

void play_sound_6(object speaker,int index) {
        object mazeobj;
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一说道：好，我可以开始作法了！\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一说道：聚灵塔需要吸收十个亡灵才能发挥作用。！\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一说道：在我施法期间，会有很多亡灵被吸引来，帮我杀够十个！\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),HIW"丁一将骨杖、幽冥之火和僵尸血投入到聚灵法阵中...法阵顿时亮了起来！\n"NOR);
                        break;
                case(4):
                        tell_room(environment(),HIY"丁一拿出聚灵塔，大声的念着咒语......\n"NOR);
                        set_temp("任务", 6, speaker);
                        break;
                default: 
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 6, mazeobj);
                                set("quest/quest_name", "超度亡灵", mazeobj);
                                set("quest/quest_desc", "护卫丁一，同时在聚灵法阵处杀死十个亡灵", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                set("quest/to_kill/亡灵", 10, mazeobj);
                                speaker->summon_undead(environment(),mazeobj);
                                //speaker->start_call_out( (:call_other,speaker, "summon_undead",environment(),mazeobj :),5);
                                //mazeobj->delete("quest/killed/亡灵",20);
                        }
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
        }
        call_out("play_sound_6",1,speaker,++index);
}

void play_sound_7(object speaker,int index) {
        object mazeobj,*objs,obj,moon;
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),HIC"\n丁一说道：成败在此一举！\n\n"NOR);
                        tell_room(environment(),BLINK HIC"\n聚灵塔升上天空，聚灵法阵发出耀眼的五彩光芒。\n\n"NOR);
                        objs = all_inventory(environment());
                        foreach(obj in objs) {
                                if(obj && obj->is_undead())
                                        obj->die();
                        }
                        break;
                case(1):
                        tell_room(environment(),HIR"一道血色的人影从聚灵法阵中漂出，投入到聚灵塔中！\n\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),HIR"丁一收回了聚灵塔，只见血色人影和丁一合而为一！\n\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),HIR"丁一满目赤红，疯狂的大笑道：哈哈哈！我成功了！我成功了！\n\n"NOR);
                        break;
                case(4):
                        tell_room(environment(),HIR"丁一狂笑道：我丁一，现在就是血魔！血魔就是我！\n\n"NOR);
                        break;
                case(5):
                        tell_room(environment(),BLINK HIR"\n丁一将聚灵塔掷向天空，只见天际竟然升起一轮血红色的月亮！\n\n");
                        moon = new("/maze/necropolis/obj/bloodmoon");
                        set("owner", speaker, moon);
                        moon->move(environment());
                        set("short", "聚灵法阵", environment());
                        objs = all_inventory(environment());
                        foreach(obj in objs) 
                                        if(obj && userp(obj))
                                                        obj->ccommand("look");
                        set("short", HIY"聚灵法阵"NOR, environment());
                        moon->hurt();
                        break;
                case(6):
                        tell_room(environment(),HIR"\n\n丁一说道：朋友们，现在是我报答你们的时候了！就是把你们变成血魔的一部分！哈哈！\n\n"NOR);
                        set_temp("任务", 7, speaker);
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 7, mazeobj);
                                set("quest/quest_name", "终结血魔", mazeobj);
                                set("quest/quest_desc", "杀死成为血魔的丁一", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                set("quest/to_kill/丁一", 1, mazeobj);
                        }
                        set("attitude", "aggressive", speaker);
                        set("bellicosity", 50000, speaker);
/*
                        set("qi",query("max_qi",  speaker)/2, speaker);
                        set("eff_qi",query("max_qi",  speaker)/2, speaker);
                        set("jing",query("max_jing",  speaker)/2, speaker);
                        set("eff_jing",query("max_jing",  speaker)/2, speaker);
                        set("sen",query("max_sen",  speaker), speaker);
                        set("eff_sen",query("max_sen",  speaker), speaker);
*/
                        objs = all_inventory(environment());
                        foreach(obj in objs) 
                                        if(obj && obj->is_character() && !obj->is_corpse() && obj!=speaker && !obj->is_undead()) {
                                                        speaker->kill_ob(obj);
                                                        obj->kill_ob(speaker);
                                        }
                        
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
                        break;

        }
        call_out("play_sound_7",1,speaker,++index);
}

void play_sound_8(string dir,int index) {
        if(!environment())
                return;

        switch (index)  {
                case(0):
                        tell_room(environment(),HIM"\n丁一喊到：这不可能！血魔！我是血魔！\n\n"NOR);
                        tell_room(environment(),HIM"\n丁一慢慢变成了一滩污血！\n\n"NOR, this_object());
                        call_out("play_sound_8",1,dir,++index);
                        break;
                /*
                case(1):
                        tell_room(environment(),HIY"副本将在一分钟后消失！\n"NOR);
                        call_out("play_sound_8",60,dir,++index);
                        break;
                case(2):
                        FUBEN_D->remove_virtual_maze(killer, "necropolis") 
                        destruct(this_object());
                        return;
                        break;
                */
        }
}