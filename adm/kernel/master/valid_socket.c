/*
名称：
        valid_socket - 保护 socket 外部函式 (efunctions)。
语法：
        int valid_socket( object caller, string function, mixed array info );

        整数 valid_socket( 物件 呼叫者, 字串 函式, 混合 阵列 资讯 );
用法：
        每一个 socket 外部函式执行之前，会先呼叫 valid_socket()。如果
        valid_socket() 传回 0，则此 socket 外部函式失败。反之，传回 1 则成
        功。第一个参数 caller 是呼叫此 socket 外部函式的物件。第二个参数
        function 是被呼叫的 socket 外部函式名称〈例如 socket_write() 或
        socket_bind()〉。第三个参数是一个资讯的阵列。如果有资讯的话，这个
        阵列的第一个元素 (element) 是被参考的档案叙述值 (file descriptor
        being referenced)。第二个元素是拥有此 socket 的物件〈物件型态〉。
        第三个元素是此 socket 的远端位址 (address of the remote end)〈字串
        型态〉。第四个元素是与 socket 相关的 (associated) 连接埠号码 (port
        number)。
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻译：
        spock@muds.net          2000.May.21.    v22 版
*/

// valid_socket: controls access to socket efunctions
int valid_socket(object eff_user, string fun, mixed *info)
{
        return 1;
}

/*
int valid_socket(object caller, string func, mixed *info)
{
        // caller 在 login_ob 里可能不会传入物件
        if( !objectp(caller) )
                return 0;

        return is_daemon(caller) || is_command(caller) || caller->is_login_ob();
}
*/