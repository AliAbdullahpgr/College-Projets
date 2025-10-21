# Blood Donation Management System

A comprehensive C++ console application for managing blood donation operations, including donor registration, recipient management, blood stock tracking, and queue-based request processing.

## Features

### 🩸 Core Functionality
- **Donor Management**: Registration, login, and blood donation tracking
- **Recipient Management**: Registration, login, and blood request system
- **Admin Panel**: Complete system oversight and queue management
- **Blood Stock Tracking**: Real-time inventory for all blood types
- **Queue System**: Fair processing of blood requests in order
- **Data Persistence**: Automatic save/load from text files

### 🔐 Security & Validation
- Input validation using regex patterns
- Email format verification
- Phone number validation
- Password strength requirements
- Age and unit constraints

### 📊 Blood Types Supported
- A+, A-, B+, B-, AB+, AB-, O+, O-
- Stock management for each type
- Donation and request tracking

## Getting Started

### Prerequisites
- C++ compiler (GCC, Clang, or MSVC)
- Standard C++ libraries support

### Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/blood-donation-system.git
cd blood-donation-system
```

2. Compile the program:
```bash
g++ -o BloodDonationSystem BloodDonationSystem.cpp
```

3. Run the application:
```bash
./BloodDonationSystem
```

## Usage

### Main Menu Options
1. **Sign Up** - Create new donor or recipient account
2. **Sign In** - Access existing account (Donor/Recipient/Admin)
3. **Exit** - Close the application

### User Roles

#### Donors
- Register with personal details and blood type
- Donate blood (1-3 units per session)
- View personal profile

#### Recipients
- Register with blood requirements
- Request blood (automatically queued)
- Track request status

#### Admin
- Default credentials: `admin@admin.com` / `admin123`
- View complete blood stock
- Process recipient queue
- System oversight

## Data Structure

The system uses several key data structures:

- **Linked Lists**: For storing donors and recipients
- **Queue**: For managing blood requests fairly
- **Structs**: For organizing user and stock data
- **File I/O**: For persistent data storage

## File Structure

```
blood-donation-system/
├── BloodDonationSystem.cpp    # Main application code
├── README.md                  # This file
├── donors.txt                 # Donor data (auto-generated)
├── recipients.txt             # Recipient data (auto-generated)
└── stock.txt                  # Blood stock data (auto-generated)
```

## Technical Details

### Input Validation
- **Name**: Alphabetic characters only
- **Email**: Standard email format validation
- **Phone**: 10-15 digit numbers with optional country code
- **Blood Group**: Valid blood type format (A+, B-, etc.)
- **Password**: Minimum 8 characters with letters and numbers
- **Age**: 1-120 years
- **Units**: 1-3 units per transaction

### Memory Management
- Dynamic memory allocation for linked list nodes
- Proper cleanup in destructor
- Queue implementation with node management

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Create a Pull Request

## Future Enhancements

- [ ] Password hashing for security
- [ ] Database integration (SQLite/MySQL)
- [ ] Blood compatibility matching
- [ ] Appointment scheduling
- [ ] Email notifications
- [ ] GUI interface
- [ ] Report generation
- [ ] Donor history tracking

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Built as a learning project to demonstrate C++ programming concepts
- Implements fundamental data structures and algorithms
- Focuses on real-world problem solving

## Contact

For questions or suggestions, please open an issue or contact aliabdullah3676@gmail.com
