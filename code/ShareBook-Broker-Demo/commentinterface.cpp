#include "commentinterface.h"

CommentInterface::CommentInterface(const std::string &tid):
    m_timeId(tid)
{

}

std::string CommentInterface::id() const
{
    return m_timeId;
}
