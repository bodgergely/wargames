Account = {balance = 0}

function Account.withdraw(self, v)
    Account.balance = Account.balance - v
    local r = Account.balance
    return r
end
