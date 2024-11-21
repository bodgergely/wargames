#curl -s -X POST -H "Content-Type: application/json" -H "Authorization: token xxxxxxxxxxxxxxxxxxxxxxxxxxx" --data "@query_issue_comments.json" https://api.github.com/graphql | jq .
curl -s -X POST -H "Content-Type: application/json" -u bodgergely --data "@query_issue_comments.json" https://api.github.com/graphql | jq .
