#include <ansi.h>

string *action_msg = ({
"南海神尼头也不抬地说：“",
"南海神尼翻出一叠档案道：“",
"南海神尼低头想了想，说道：“",
"南海神尼忧心忡忡的说：“",
"南海神尼微微笑了笑道：“",
"南海神尼斩钉截铁的说道：“",
"南海神尼背着双手跺着步，一字一字的对你说：“",
"南海神尼轻轻叹息到：“",
"南海神尼突发奇想道：“",
});

string *say_msg1 = ({
"我突然想起需要一样东西，就是name",
"我想这样子，你不如去找找name",
"你现在就去，快点寻一寻name",
"武林大会就要召开，目前正需要name",
"现在有一件急事要你办，就是去找来name",
"我这里正想找人抓差，你去把name",
"你现在去四处看看，有没有name",
"让你赶快去做一件事，也就是找name",
"养兵千日，用兵一时，看看你的办事能力，去搞来name",
"我怎么还没有name",
"你难道还不知道我现在需要什么？name",
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
"，找了来就看出你的办事能力了",
"，速去速回",
"这个物件，快想办法去吧",
"交给我，怎么样，不会太难吧",
});

string *kill_msg1 = ({
"name这个人违背江湖道义，",
"你听说过name最近出卖朋友的事情么？",
"人人都说name老是胡作非为，",
"name胆子竟然那么大？居然也敢辱骂武林同盟！",
"听说name一心想替我而代之？",
"侮辱朋友的妻子，name是狗胆包天了，",
"有一伙人最近打着我的旗号四处招摇撞骗，我已经查出其中有name，",
"江湖有江湖的道义，name最近的所作所为实在不象话！",
"你去找找看name在什么地方，杀了我们的兄弟躲起来就行了？",
});

string *kill_msg2 = ({
"这种人岂能活在世界上！”",
"你去杀了这个家伙吧。”",
"对这种人就不要心慈手软了。”",
"把name送到阎王那里去吧！”",
"杀了name，干净利索点。”",
"为了维持江湖道义，也只有杀了name了。”",
});

string query_snmsg(string type,string name)
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
        } else
        {
                msg1 = kill_msg1[random(sizeof(kill_msg1))];
                msg1 = replace_string(msg1,"name",name);
                msg2 = kill_msg2[random(sizeof(kill_msg2))];
                msg2 = replace_string(msg2,"name",name);
        }
        msg += msg1;
        msg += msg2;
        return msg;
}
