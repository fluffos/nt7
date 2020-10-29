// This program is a part of NT MudLIB
// 笑傲江湖

#include <ansi.h>

#define DEBOOKS "笑傲江湖"

// 序章开始时调用的剧情简介
string *BookMsg = ({
        "其时武林之中，既有正邪之判，复存门户之别，少林、武当、青城、五岳自诩正教与魔教（日月神教）冤冤相报，誓不两立。",
        "五岳剑派名虽一体，实存芥蒂。嵩山掌门左冷禅野心勃勃，意欲吞并五岳，称霸江湖，自恃盟主身份，凌驾四岳掌门，挑拨华山剑宗争夺掌门之位。",
        "岳不群原属气宗，剑、气二宗素不相和，不群率本门弟子外出避祸，遭左道之士埋伏，俱被擒获。",
        "江湖之中流传着一个传说，林家祖传的《辟邪剑法》乃天下无敌之武功，谁能练成将天下无敌！",
        "福建林远图以七十二路辟邪剑法称雄武林，创立福威镖局，笑傲江湖，驰骋天下。",
        "远图死后，子孙无能，四方豪杰觊觎辟邪剑谱，纷至沓来 ……",
        "辟邪剑谱之争，武林盟主之争，由此拉开序幕！",
});

mapping book_list = ([

        "1"     :    ([ "当前章节" : "第一章",
                        "当前任务" : "路见不平",
                        "任务描述" : "青城派弟子欺辱一个文弱公子，你路见不平，拔刀相助。",
                        "loadboss" : "qcdz.data",  // 建立副本，生成boss,进入副本战斗
                        
                        //"任务状态" : 0,
                        //"任务编号" : "1",
                        
                        "下个任务" : "5", ]),
        "5"     :    ([ "当前章节" : "第一章",
                        "当前任务" : "青城四少",
                        "任务描述" : "青城派弟子带来了帮手，传说中的青城四少，看样子你不得不动武了。",
                        "下个任务" : "10", ]),
]);

mapping query_book_list(string n)
{
        if( undefinedp(book_list[n]) ) return 0;
        return book_list[n];
}

// 来自 /cmds/usr/skybook.c调用，开始天书任务
void startbook(object me, string sBook)
{
        string sQuest; // 当前任务编号
        string sZhangjie; // 当前章节
        object ob, ob2;

        sZhangjie = me->query("skybook14/" + sBook + "/当前章节");
        sQuest = me->query("skybook14/" + sBook + "/任务编号"); // 表示还没有完成的任务编号
        

        if (sQuest == "1")
        {
                DIALOG_D->start_dialog4(this_object(), me, sBookMsg, 0, 1);
                return;
        }
        
        
        FUBEN_D->move_all_invalid_user(me);
        
        move_to_room(me, sQuest);

        return;

}

// 副本全部通关，大结局
void endskybook(object me)
{

        // 通知玩家完成了该天书
        tell_object(me, BLINK + HIY "\n恭喜你！成功通关《" + DEBOOKS + "》天书！\n\n" NOR);
        
        // 广播全服
        CHANNEL_D->do_channel(this_object(),"rumor", "听说" + HIY + me->query("name")  + "(" + me->query("id") + ")" HIM "闯关《" + DEBOOKS + "》天书成功！\n");
                
        log_file("通关天书", me->query("id") + " at " + ctime(time()) + " 通关 " + DEBOOKS  + "\n" );
                
        // 累积该完成次数
        me->add("skybook14/option/" + DEBOOKS + "/completed_times", 1);
        
        // 给予通关固定奖励
        GIFT_D->delay_bonus(me,
                ([ "exp"      : 5000000,
                   "pot"      : 5000000,
                   "mar"      : 5000000,
                   "prompt"   : "你在通关《" +  DEBOOKS + "》天书后" ]), 999);  

        // 给予通关随机奖励
        SUICONG_D->give_end_gift(me, DEBOOKS, me->query("skybook14/" + DEBOOKS + "/难度"));

        return;
        
}
