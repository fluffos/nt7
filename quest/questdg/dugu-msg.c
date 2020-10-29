#include <ansi.h>

string *action_msg = ({
"独孤求败微笑着对你说：“",
"独孤求败满脸正容道：“",
"独孤求败呵呵大笑着说：“",
"独孤求败忧心忡忡的说：“",
"独孤求败缓缓的告诉你：“",
"独孤求败一脸和蔼的说道：“",
"独孤求败背着双手踱着步，严肃的说：“",
"独孤求败轻轻叹息到：“",
"独孤求败正容对你道：“",
});

string *say_msg1 = ({
"我突然想起需要一样东西，就是name",
"我想这样子，你不如去找找name",
"你现在就去，帮我寻一寻name",
"江湖动荡，物资紧缺，我目前正想要name",
"现在有一件急事要你做，就是去帮我找name",
"你有空就去四处看看，是否能弄来name",
"我想请你赶快帮我做一件事，也就是找name",
"年轻人需要多锻炼锻炼，看看你的办事能力，去搞来name",
"我突然很想看看name",
"听说有一样东西叫name",
"天下大部分东西我都有了，不过少了一样name",
});

string *say_msg2 = ({
"，你能不能把它找来呢",
"，我想你应该可以完成任务吧",
"，仔细找一找，应该不难的",
"，速速找来交给我要紧",
"，要是能找来，我自会奖励你",
"，能不能寻到它呢？",
"，能否找来就看出你的办事能力了",
"，速去速回",
"这个物件，快想办法去吧",
"交给我，怎么样，不会太难吧",
});

string *kill_msg1 = ({
"name这个人素来多行不义，",
"你听说过name最近犯下的滔天罪行吧？",
"有人向我反映name老是胡作非为，",
"name竟然诱拐良家妇女！",
"听说name最近帮太行山土匪领路，打劫了一个镇子，",
"对朋友坑蒙拐骗，name这个人毫无仁义道德，",
"有一伙人最近冒充我四处招摇撞骗，我已经查出其中有name，",
"做错事情可以改，一错再错，我也维护不了name，",
"你去找找name在什么地方，这个人犯下的罪行连神都不会原谅，",
});

string *kill_msg2 = ({
"这种人多一个不如少一个！”",
"你去铲除了这个恶霸吧。”",
"对这种人就不要心慈手软了。”",
"把name送到地狱去好好反省吧！”",
"锄了name，不要心慈手软！”",
"为了维护江湖的公德，也只有杀了name了。”",
});

string *summon_msg1 = ({
"name这个人本性不坏，我倒是有心维护一下，",
"你听说过name最近犯了点错误吧？",
"有人向我反映name老是胡作非为，",
"name好好一个人，怎么突然也干坏事？",
"听说name最近去过太行山土匪窝，不知道想干什么？",
"犯了错误，要及时改正啊，name现在需要指引才能走上正道，",
"你去找找name在什么地方，",
});

string *summon_msg2 = ({
"你把name给我带这里来吧！”",
"帮我去把name擒来。”",
"带name来我这里，我来教育教育。”",
"不知道name来我这里会不会听我的指导！”",
"我真想当面好好的责问一下name！”",
});

string query_dgmsg(string type,string name)
{
        string msg,msg1,msg2;
        msg = "";
        msg1 = "";
        msg2 = "";
        msg += action_msg[random(sizeof(action_msg))];
        if (type == "寻") {
                msg1 = say_msg1[random(sizeof(say_msg1))];
                msg1 = replace_string(msg1,"name",name);
                msg2 = say_msg2[random(sizeof(say_msg2))];
                msg2 = replace_string(msg2,"name",name);
        } else if (type == "杀" || type == "宰")
        {
                msg1 = kill_msg1[random(sizeof(kill_msg1))];
                msg1 = replace_string(msg1,"name",name);
                msg2 = kill_msg2[random(sizeof(kill_msg2))];
                msg2 = replace_string(msg2,"name",name);
        } else if (type == "捉" || type == "擒")
        {
                msg1 = summon_msg1[random(sizeof(summon_msg1))];
                msg1 = replace_string(msg1,"name",name);
                msg2 = summon_msg2[random(sizeof(summon_msg2))];
                msg2 = replace_string(msg2,"name",name);
        }
        msg += msg1;
        msg += msg2;
        return msg;
}
