#ifndef UTILS_H
#define UTILS_H

#define CHECK(cond) do {if (!cond) {qCritical() << "ASSERT:" << #cond << "in" << __FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")"; Q_ASSERT(cond);}} while(0)

#define POS "; FUNC" << __FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")"

#endif // UTILS_H
